/*
 * Mapper.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: alpha
 */

#include "Mapper.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Mapper, "Messages specific for this example");
Mapper::Mapper(string thisName, string appMas, string nameNode, string DataNode,
		allocateRes *res) {
	this->merger = nullptr;

	this->mid = mapIds++;
	this->dataNodeName = DataNode;
	this->thisName = thisName;
	this->appMasterName = appMas;
	this->nameNodeName = nameNode;
	this->res = res;
	nodeManagerName = res->nodeManager;
	nodeManagerMb = Mailbox::by_name(nodeManagerName);
	this->job = res->job;
	nnmb = Mailbox::by_name(nameNodeName);
	string mbForDn = thisName + "_dn";
	thismbForDataNode = Mailbox::by_name(mbForDn);
	hddm = new HddMediator(dataNodeName, mbForDn,thisName );
	dataNodeMb = Mailbox::by_name(dataNodeName);
	appMasterMb = Mailbox::by_name(appMasterName);
	thismb = Mailbox::by_name(thisName);



	////XBT_INFO("create map task");

}

void Mapper::operator ()() {
	double startt = Engine::get_clock();
	this_actor::sleep_for(this->job->taskStartTime);

	thismb->set_receiver(Actor::self());
	thismbForDataNode->set_receiver(Actor::self());
	if (res->type == allocate_type::reduce_all) {
		//      XBT_INFO("error allocate type error %i   ,%s", res->type,
		//		this_actor::get_name().c_str());
		exit(1);
	}

	string inputDN = selectInputDataNode();

	HddMediator *inputHDDM = new HddMediator(inputDN, thisName, thisName);
	Chunk *ch = res->dir->Files->at(to_string(res->fIndex))->chunks->at(
			res->chIndex);

	inputHDDM->readCh(ch);

	job->ctr->addToCtr(ctr_t::MAP_INPUT_SIZE, (double) ch->size);
////// untill now we read the chunk from data node

	int64_t spillSize = int64_t(
			job->ioSortMb * 1024 * 1024 * job->ioSortSpillPercent);
	//int64_t spillSize = int64_t(job->ioSortMb * 1024 * 1024);
	double taskSize = (double) ch->size;
	double mapRecords = taskSize / job->recordSize;
	this->mapRecCount = mapRecords;
	job->ctr->addToCtr(ctr_t::MAP_INPUT_RECORDS, (double) mapRecords);

	merger = new Combiner(job, dataNodeName, thisName, mapRecords,thismbForDataNode->get_name());
	auto exePtr = this_actor::exec_async((double) (job->mapCost * mapRecords)); //here we exe the map

	map<int, vector<spill*>*> *allspilles = this->writeSpilles(taskSize,
			spillSize); //here we use partitioner and combiner and write spilles to localhdd

	exePtr->wait();

//	exit(0);

	for (int i = 0; i < allspilles->size(); i++) {

		merger->mergeSpilles(allspilles->at(i));
	}



	Message *finishMsg = new Message(msg_type::map_finish, thisName,
			appMasterName, 0, allspilles);

//	////XBT_INFO("before send finish");
	appMasterMb->put(finishMsg, 1522);
	Message *finishMsg2 = new Message(msg_type::map_finish, thisName,
			nodeManagerName, 0, nullptr);
	nodeManagerMb->put(finishMsg2, 1522);
	////////XBT_INFO("after send finish");
	delete ch;

	double stopt = Engine::get_clock();
	job->ctr->addToCtr(ctr_t::avMappersTime, stopt - startt);
}
Mapper::~Mapper() {
	// TODO Auto-generated destructor stub
}
int64_t Mapper::mapIds = 0;

void Mapper::init() {

}
string Mapper::selectInputDataNode() {
	Chunk *ch = res->dir->Files->at(to_string(res->fIndex))->chunks->at(
			res->chIndex);
	string inputdataNode = "";
	int numNode = ch->nodes->size();
	bool isLocality = false;
	for (int n = 0; n < numNode; n++) { //check if the chunk node is this datanode
		Mailbox *dataNode = ch->nodes->at(n);
		string dnName = dataNode->get_name();
		if (this->dataNodeName.compare(dnName) == 0) {
			isLocality = true;
			inputdataNode = dataNodeName;
			job->ctr->addToCtr(ctr_t::Data_local_map_tasks, 1);
			////XBT_INFO("is locality");
			break;
		}
	}
	if (!isLocality) { //find data node in the same rack
		string thisRack = this_actor::get_host()->get_property("rack");
		Engine *e = simgrid::s4u::Engine::get_instance();

		auto hosts = e->get_all_hosts();
		for (int n = 0; n < numNode; n++) {
			Mailbox *dataNode = ch->nodes->at(n);
			string dnName = dataNode->get_name();
			string hostn = dnName.substr(0, dnName.find("_"));
			auto host = e->host_by_name(hostn);
			if (thisRack.compare(host->get_property("rack")) == 0) {
				inputdataNode = dnName;
				isLocality = true;
				break;
			}

		}
		if (!isLocality) { //return rand datanode
			int nodeIndex = RandClass::getRand(0, numNode - 1);
			inputdataNode = ch->nodes->at(nodeIndex)->get_name();
		}

		return inputdataNode;

	}

}
map<int, vector<spill*>*>* Mapper::writeSpilles(double taskSize,
		int64_t spillSize) {
	map<int, vector<spill*>*> *spilles = new map<int, vector<spill*>*>();
	int64_t tt = (taskSize / job->recordSize) * job->mapOutRecords
			* job->mapOutAvRecordSize;

	job->ctr->addToCtr(ctr_t::MAP_OUTPUT_SIZE, (double) tt);
	job->ctr->addToCtr(ctr_t::MAP_OUTPUT_RECORDS,
			(double) (tt / job->mapOutAvRecordSize));

	merger->mapRecNum = (double) (tt / job->mapOutAvRecordSize);

	int64_t memSpill = 1;
	if (tt > memSpill) {
		tt -= memSpill;
	} else {
		memSpill = tt;
		tt = 0;

	}

	int64_t spillNum = tt / spillSize;

	int64_t allS = spillNum + 1; //1 for mem spill

	if (tt % spillSize != 0)
		allS++;

	if (allS < job->mapCombineMinspills) //this for compression before write to desk
		minFilesToCombine = true;
	else
		minFilesToCombine = false;

	bool inMemSpill = false;
    assert(spillNum!=0);
	for (int i = 0; i < job->numberOfReducers; i++) {

		vector<spill*> *vectorSpill = new vector<spill*>();
		spilles->insert(std::pair<int, vector<spill*>*>(i, vectorSpill));

		for (int j = 0; j < spillNum; j++) {

			int64_t partsize = spillSize / job->numberOfReducers;
			spill *tem;
			if (inMemSpill)
				tem = exePart(partsize);
			else
				tem = exeAndWrPart(partsize);
			spilles->at(i)->push_back(tem);
			//////XBT_INFO("push spill so size is %i ", spilles->size());
		}
		inMemSpill = false;

	}

	if (tt % spillSize != 0) {
		int64_t reminderSize = tt - (spillSize * spillNum);

		for (int i = 0; i < job->numberOfReducers; i++) {

			int64_t partsize = reminderSize / job->numberOfReducers;
			////XBT_INFO("remender size is %i part %i", reminderSize, partsize);
			spill *tem = exeAndWrPart(partsize);
			spilles->at(i)->push_back(tem);

		}

	}

	//for mem spill
	for (int i = 0; i < job->numberOfReducers; i++) {

		int64_t partsize = memSpill / job->numberOfReducers;
		////XBT_INFO("remender size is %i part %i", memSpill, partsize);
		spill *tem = exePart(partsize);
		spilles->at(i)->push_back(tem);

	}

	return spilles;
}
/*int64_t Mapper::combine(int64_t recNum) {
 int64_t combinedRecs = 0;
 if (job->useCombiner) {

 combinedRecs = merger->getNumCombinedRecordes(job->combineGroups,
 recNum);
 //////XBT_INFO("in compiner ,num rec is %i old is %i", combinedRecs,recNum);

 } else {
 combinedRecs = recNum;
 //	////XBT_INFO(" in compiner  no co ,num rec is %i", combinedRecs);
 }
 return combinedRecs;

 }*/

spill* Mapper::exeAndWrPart(int64_t partsize1) {

	int64_t partsize = 0;
	int64_t partrecNum = partsize1 / job->mapOutAvRecordSize;

	int64_t combinedRecs = merger->combine(partrecNum);


	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, (double) combinedRecs);
	job->ctr->addToCtr(ctr_t::map_spilled_recordes, (double) combinedRecs);
	job->ctr->addToCtr(ctr_t::map_file_bytes_write, (double) partsize1);
	ExecPtr ptrE;

	double comp_cost;
	if (minFilesToCombine && job->useCompression) //so compress here
		comp_cost = (double) partrecNum * job->compressionCost;
	else
		comp_cost = 0;

	if (partrecNum == combinedRecs) {
		ptrE = this_actor::exec_async(comp_cost);
		partsize = partsize1;
		//////XBT_INFO("no compiiner so size is %i", partsize);

	} else {
		partsize = combinedRecs * job->combineOutAvRecordSize;
		ptrE = this_actor::exec_async(
				(double)( partrecNum * job->combineCost + comp_cost)); //the cost of combination = combine rec cost * map recs
		//////XBT_INFO("yes compiiner so size is %i", partsize);
	}

	if (!minFilesToCombine && job->useCompression)		//for size
		partsize *= job->compressionSize;		//compress
	//XBT_INFO(" before exe and %i",partsize);

	Chunk *temC = this->hddm->writeCh(partsize);

	ptrE->wait();
	//untill now we write spill after partition it and execute it

	spill *tem = new spill();
	tem->ch = temC;
	tem->taskName = thisName;
	tem->records = combinedRecs;

	return tem;
}

spill* Mapper::exePart(int64_t partsize1) {

	int64_t partsize = 0;
	int64_t partrecNum = partsize1 / job->mapOutAvRecordSize;
	int64_t combinedRecs = partrecNum;

	ExecPtr ptrE;

	double comp_cost;
	if (minFilesToCombine && job->useCompression)		//so compress here
		comp_cost = (double) partrecNum * job->compressionCost;
	else
		comp_cost = 0;

	if (partrecNum == combinedRecs) {
		ptrE = this_actor::exec_async(comp_cost);
		partsize = partsize1;
		//////XBT_INFO("no compiiner so size is %i", partsize);

	} else {
		partsize = combinedRecs * job->combineOutAvRecordSize;
		ptrE = this_actor::exec_async(
				(double) partrecNum * job->combineCost + comp_cost); //the cost of combination = combine rec cost * map recs
		//////XBT_INFO("yes compiiner so size is %i", partsize);
	}

	if (!minFilesToCombine && job->useCompression)		//for size
		partsize *= job->compressionSize;		//compress
	Chunk *temC;

	spill *tem = new spill();
	if (job->useCombiner) {
		temC = this->hddm->writeCh(partsize);
		tem->isInMem = false;
		job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, (double) combinedRecs);
		job->ctr->addToCtr(ctr_t::map_spilled_recordes, (double) combinedRecs);
	} else {
		temC = new Chunk(thisName, thisName, 0, partsize);
		temC->clinetMB = thismb;
		tem->isInMem = true;
	}

	ptrE->wait();
	//untill now we write spill after partition it and execute it

	tem->ch = temC;
	tem->taskName = thisName;
	tem->records = combinedRecs;

	return tem;
}

string Mapper::printSpill(spill *sp) {
	string s = "";
	s += "spill size is " + to_string(sp->ch->size);
	s += "num rec  is " + to_string(sp->records);
	s += "is last  one  " + to_string(sp->isLast);
	return s;
}

string Mapper::printMapOut(map<int, vector<spill*>*> *a) {
	string s = "this is the output of mapper " + thisName + " \n";
	for (int i = 0; i < a->size(); i++) {
		s += "the spiller of reducer number " + to_string(i) + "\n";
		for (int j = 0; j < a->at(i)->size(); j++) {
			s += printSpill(a->at(i)->at(j)) + "\n";
		}
	}

	s += "\n";
	return s;
}

double Mapper::copress(double s) {
	double res;
	res = s * this->job->compressionSize;

	return res;
}
