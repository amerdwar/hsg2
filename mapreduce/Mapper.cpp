/*
 * Mapper.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: alpha
 */

#include "Mapper.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Mapper, "Messages specific for this example");
Mapper::Mapper(string thisName, string appMas, string nameNode, string DataNode,
		allocateRes * res) {

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
	hddm = new HddMediator(dataNodeName, thisName, thisName);
	dataNodeMb = Mailbox::by_name(dataNodeName);
	appMasterMb = Mailbox::by_name(appMasterName);
	thismb = Mailbox::by_name(thisName);
	XBT_INFO("create map task");
	merger = new Combiner(job, dataNodeName, thisName);
}

void Mapper::operator ()() {
	thismb->set_receiver(Actor::self());
	if (res->type == allocate_type::reduce_all) {
		XBT_INFO("error allocate type error %i   ,%s", res->type,
				this_actor::get_name().c_str());
		exit(1);
	}

	string inputDN = selectInputDataNode();

	HddMediator* inputHDDM = new HddMediator(inputDN, thisName, thisName);
	Chunk* ch = res->dir->Files->at(to_string(res->fIndex))->chunks->at(
			res->chIndex);


	inputHDDM->readCh(ch);

////// untill now we read the chunk from data node

	int64_t spillSize = int64_t(job->ioSortMb * 1024 * 1024);
	int64_t taskSize = ch->size;

	auto exePtr = this_actor::exec_async(job->mapCost); //here we exe the map

	map<int, vector<spill*>*>* allspilles = this->writeSpilles(taskSize,
			spillSize); //here we use partitioner and combiner and write spilles to localhdd

	exePtr->wait();


	for (int i = 0; i < allspilles->size(); i++) {
		merger->mergeSpilles(allspilles->at(i));
	}

//	XBT_INFO(printMapOut(allspilles).c_str());



	Message* finishMsg = new Message(msg_type::map_finish, thisName,
			appMasterName, 0, allspilles);

//	XBT_INFO("before send finish");
	appMasterMb->put(finishMsg, 1522);
	Message * finishMsg2 = new Message(msg_type::map_finish, thisName,
			nodeManagerName, 0, nullptr);
	nodeManagerMb->put(finishMsg2, 1522);
	//XBT_INFO("after send finish");

}
Mapper::~Mapper() {
	// TODO Auto-generated destructor stub
}
int64_t Mapper::mapIds = 0;

void Mapper::init() {

}
string Mapper::selectInputDataNode() {
	Chunk* ch = res->dir->Files->at(to_string(res->fIndex))->chunks->at(
			res->chIndex);
	string inputdataNode = "";
	int numNode = ch->nodes->size();
	bool isLocality = false;
	for (int n = 0; n < numNode; n++) { //check if the chunk node is this datanode
		MailboxPtr dataNode = ch->nodes->at(n);
		string dnName = dataNode->get_name();
		if (this->dataNodeName.compare(dnName) == 0) {
			isLocality = true;
			inputdataNode = dataNodeName;
			break;
		}
	}
	if (!isLocality) { //find data node in the same rack
		string thisRack = this_actor::get_host()->get_property("rack");
		Engine* e = simgrid::s4u::Engine::get_instance();

		auto hosts = e->get_all_hosts();
		for (int n = 0; n < numNode; n++) {
			MailboxPtr dataNode = ch->nodes->at(n);
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
map<int, vector<spill*>*>* Mapper::writeSpilles(int64_t taskSize,
		int64_t spillSize) {
	map<int, vector<spill*>*>* spilles = new map<int, vector<spill*>*>();
int64_t tt=(taskSize/job->recordSize)*job->mapOutRecord*job->mapOutAvRecordSize;
	int64_t spillNum = tt / spillSize;
	//XBT_INFO("spill size %i spill num %i task size %i", spillSize, spillNum,
		//	taskSize);
	for (int i = 0; i < job->numberOfReducers; i++) {
		vector<spill*>* vectorSpill = new vector<spill*>();
		spilles->insert(std::pair<int, vector<spill*>*>(i, vectorSpill));
		for (int j = 0; j < spillNum; j++) {

			int64_t partsize = spillSize / job->numberOfReducers;
			spill* tem = exeAndWrPart(partsize);
			spilles->at(i)->push_back(tem);
			//XBT_INFO("push spill so size is %i ", spilles->size());
		}

	}

	if (tt % spillSize != 0) {
		int64_t reminderSize = tt - (spillSize * spillNum);

		vector<spill*>* vectorSpill = new vector<spill*>();
		for (int i = 0; i < job->numberOfReducers; i++) {

			int64_t partsize = reminderSize / job->numberOfReducers;
			XBT_INFO("remender size is %i part %i", reminderSize, partsize);
			spill* tem = exeAndWrPart(partsize);
			spilles->at(i)->push_back(tem);

		}

	}

	return spilles;
}
int64_t Mapper::combine(int64_t recNum) {
	int64_t combinedRecs = 0;
	if (job->useCombiner) {

		combinedRecs = merger->getNumCombinedRecordes(job->combineGroups,
				recNum);
		//XBT_INFO("in compiner ,num rec is %i old is %i", combinedRecs,recNum);

	} else {
		combinedRecs = recNum;
	//	XBT_INFO(" in compiner  no co ,num rec is %i", combinedRecs);
	}
	return combinedRecs;

}

spill* Mapper::exeAndWrPart(int64_t partsize1) {

	int64_t partsize = 0;
	int64_t partrecNum = partsize1 / job->mapOutAvRecordSize;

	//XBT_INFO("part size %i, record size %i, num rec per part %i", partsize1,
			//job->recordSize, partrecNum);

	//XBT_INFO("part size %i, record size %i, num rec per part %i , new rec num%i", partsize1,
		//	job->recordSize, partrecNum,partrecNum);
	int64_t combinedRecs = combine(partrecNum);
	ExecPtr ptrE;
	if (partrecNum == combinedRecs) {
		ptrE = this_actor::exec_async(0);
		partsize = partsize1;
		//XBT_INFO("no compiiner so size is %i", partsize);

	} else {
		partsize = combinedRecs * job->combineOutAvRecordSize;
		ptrE = this_actor::exec_async((double) partrecNum * job->combineCost); //the cost of combination = combine rec cost * map recs
		//XBT_INFO("yes compiiner so size is %i", partsize);
	}

	Chunk* temC = this->hddm->writeCh(partsize);
	ptrE->wait();
	//untill now we write spill after partition it and execute it

	spill* tem = new spill();
	tem->ch = temC;
tem->taskName=thisName;
	tem->records = combinedRecs;

	return tem;
}

string Mapper::printSpill(spill* sp) {
	string s = "";
	s += "spill size is " + to_string(sp->ch->size);
	s += "num rec  is " + to_string(sp->records);
	s += "is last  one  " + to_string(sp->isLast);
	return s;
}

string Mapper::printMapOut(map<int, vector<spill*>*>*a) {
	string s = "this is the output of mapper "+thisName+" \n";
for(int i=0;i<a->size();i++){
	s+="the spiller of reducer number "+to_string(i)+"\n";
	for(int j=0;j<a->at(i)->size();j++){
		s+=printSpill(a->at(i)->at(j))+"\n";
	}
}

	s+="\n";
	return s;
}
