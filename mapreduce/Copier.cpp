/*
 * Copier.cpp
 *
 *  Created on: Mar 30, 2019
 *      Author: alpha
 */

#include "Copier.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Copier, "Messages specific for this example");
Copier::Copier(string thisName, string parent, int nCopiers, JobInfo* job,
		string datNodeName) {
	this->job = job;
	q = new queue<vector<spill*>*>();

	this->nCopiers = nCopiers;
	this->nFreeCopiers = nCopiers;
	this->parent = parent;
	this->thisName = thisName;
	this->dataNode = datNodeName;
	this->memBytes = int64_t(
			job->memoryLimit );

	this->bufferMemBytes = int64_t(
			job->memoryLimit * job->mapredJobReduceInputBufferPercent);

	merger = new Combiner(job, dataNode, thisName);
	thismb = Mailbox::by_name(thisName);
	string mbForDn = thisName + "_dn";
	thismbForDataNode = Mailbox::by_name(mbForDn);
	parentMb = Mailbox::by_name(parent);
	hddmed = new HddMediator(dataNode, mbForDn, thisName);
	outMemV = new vector<spill*>();
	outDiskV = new vector<spill*>();
}

void Copier::operator()() {

	thismb->set_receiver(Actor::self());
	thismbForDataNode->set_receiver(Actor::self());
	Message* m = nullptr;
	bool isFinish = false;
	do {

		m = static_cast<Message*>(thismb->get());
		////XBT_INFO("in copier");
		switch (m->type) {

		case msg_type::finish_copier: {
			//XBT_INFO("copier  finish ");
			isFinish = true;
			//XBT_INFO("this is %i %i", reqNum, ackNum);
			//XBT_INFO(printMap(readVAck).c_str());
			//send finish to parent
			break;
		}
		case msg_type::cl_dn_re_ch: {
			//	//XBT_INFO("in copier");

			vector<spill*>* vt = static_cast<vector<spill*>*>(m->payload);

			vector<vector<spill*>*>* allV = getMapsVecors(vt);

			for (int i = 0; i < allV->size(); i++) {

				//	//XBT_INFO("in read vector spill %i",
				//allV->at(i)->at(0)->ch->nodes->size());

				string mapDnName = allV->at(i)->at(0)->ch->dirName;
				////XBT_INFO("th is the name %s",mapDnName.c_str());
				//exit(0);
				//	//XBT_INFO("datanode is %s",	allV->at(i)->at(0)->ch->nodes->at(0)->get_name().c_str());
				int mapSpillNum = allV->at(i)->size();
				readVAck.insert(std::pair<string, int>(mapDnName, mapSpillNum));

				if (nFreeCopiers > 0) {
					sendReadReg(allV->at(i));
					spillAndCompine(exe(allV->at(i))); //here the sort combine and spill to mem and hdd
					nFreeCopiers--;
				} else {
					q->push(allV->at(i));
				}
			}
			break;
		}
		case msg_type::dn_cl_re_ack_ch: {

			//XBT_INFO("sender is %s", m->mapperName.c_str());
			readVAck.at(m->mapperName)--;

			if
(			readVAck.at(m->mapperName)==0) {
				ackNum++;
				if (q->size() > 0) {

					sendReadReg(q->front());
					spillAndCompine(exe(q->front())); //here the sort combine and spill to mem and hdd
					q->pop();
				} else {
					nFreeCopiers++;
				}
			}
			break;
		}

		}

		if (isFinish && ackNum == reqNum) {
			//XBT_INFO("end copier %i ,%i  ,%i %i", isFinish, ackNum, reqNum,
				//	q->size());
			//XBT_INFO("the all size is %s", to_string(numBytes).c_str());

			break;

		}
	} while (true);
	for (auto aa : pending_comms)
		aa->wait();
for (auto pp:actorPtrV)
	pp->join();

	Message *cpF1 = new Message(msg_type::finish_copier, this->thisName, parent,
			0, outMemV);

	Message *cpF2 = new Message(msg_type::finish_copier, this->thisName, parent,
			0, outDiskV);
	parentMb->put(cpF1, 0);
	parentMb->put(cpF2, 0);

}

Copier::~Copier() {
	// TODO Auto-generated destructor stub
}

void Copier::sendReadReg(vector<spill*> *v) {

	MailboxPtr dnmb = v->at(0)->ch->nodes->at(0);
	string dn = dnmb->get_name();



	reqNum++;
	for (int i = 0; i < v->size(); i++) {

		//add shuffled bytes
		//if (this->dataNode.compare(dn)!=0)
		job->ctr->addToCtr(ctr_t::REDUCE_SHUFFLE_BYTES,v->at(i)->ch->size);
		job->ctr->addToCtr(ctr_t::REDUCE_INPUT_RECORDS,v->at(i)->records);
		Message *chReq = new Message(msg_type::cl_dn_re_ch, this->thisName, dn,
				hdd_Access::hdd_read, v->at(i)->ch);

		string mapDnName = v->at(0)->ch->dirName;

		chReq->mapperName = mapDnName;
		//send the request of chunk to data node

		if(dnmb->get_name()==this->dataNode){

		dnmb->put(chReq, 0);
		}else{

			dnmb->put(chReq, 1522);
		}



////XBT_INFO("message %s",chReq->traceStr.c_str());
		//ExecPtr exep=this_actor::exec_async(ch->size);
	}

}

spill* Copier::exe(vector<spill*>* v) { //execute the
	spill* lastsp = v->at(0);

	for (int i = 1; i < v->size(); i++) {
		lastsp->records += v->at(i)->records;
		lastsp->ch->size += v->at(i)->ch->size;

	}
	int64_t sss = numBytes;
	numBytes += lastsp->ch->size;
	if (numBytes < 0) {
		//XBT_INFO("error %i , %i %i ", numBytes, sss, lastsp->ch->size);
	}
//exe for merge
	double comp_cost = 0;
	if (job->useCompression)
		comp_cost = (double) lastsp->records * job->uncompressionCost;

	double exeFlops = (double) lastsp->records + comp_cost;

	if (job->useCompression) {
		//XBT_INFO("size before uncompres %s",
		//		to_string(lastsp->ch->size).c_str());

		lastsp->ch->size = (int64_t) lastsp->ch->size / job->compressionSize;

		//XBT_INFO("size after uncompres %s",
		//		to_string(lastsp->ch->size).c_str());
	}
	auto a = this_actor::exec_async(exeFlops);
	pending_comms.push_back(a); //tell now we execute one out

	return lastsp;
}

vector<vector<spill*>*> * Copier::getMapsVecors(vector<spill*>* v) {

	vector<vector<spill*>*> * allv = new vector<vector<spill*>*>();
	if (v->size() <= 1) {

		allv->push_back(v);
	} else {

		string s = v->at(0)->ch->dirName;
		vector<spill*>* firstO = new vector<spill*>();
		int c = 0;
		allv->push_back(firstO);
		allv->at(c)->push_back(v->at(0));
		for (int i = 1; i < v->size(); i++) {

			if (s.compare(v->at(i)->ch->dirName) == 0) {

				allv->at(c)->push_back(v->at(i));
				//	//XBT_INFO("add to if  %s", s.c_str());
			} else {		//new out

				vector<spill*>* tem = new vector<spill*>();
				c++;
				allv->push_back(tem);
				s = v->at(i)->ch->dirName;
				allv->at(c)->push_back(v->at(i));
				////XBT_INFO("add to else  %s", s.c_str());
			}
		}
	}
	////XBT_INFO("size is   %i", allv->size());
	return allv;
}

void Copier::spillAndCompine(spill* sp) {
	int64_t chSize = sp->ch->size;
//TODO if spill size > buffer percent write to disk directly
	if (chSize > bufferMemBytes) {
		AsyncDirectSpill(sp);
////XBT_INFO("after write direct");

		return;
	}

	if (memBytes > chSize) {
		memBytes -= chSize;
		sp->isInMem = true;
		outMemV->push_back(sp);

	} else {
		int64_t recSize = chSize / sp->records;

		int64_t memChSize = memBytes; //write in to memory
		chSize -= memChSize; //the remender
		memBytes = 0;
		//create memory spill
		spill* memSp = new spill();
		Chunk* memCh = new Chunk(parent, parent, 0, memChSize);
		memSp->ch = memCh;
		memSp->records = memChSize / recSize;
		memSp->isInMem = true;
		outMemV->push_back(memSp);

		//TODO spill all so membytes will return		recall the this function
		toDisk();

		memBytes = (int64_t) (job->memoryLimit
				* job->mapredJobShuffleMergePercent);

		sp->ch->size = chSize;
		sp->records = chSize / recSize;
		spillAndCompine(sp);
	}

}

void Copier::AsyncDirectSpill(spill* sp) {
	//cpu cost for spill to disk
	double exeFlops = (double) sp->records;
	auto a = this_actor::exec_async(exeFlops);
	pending_comms.push_back(a);


	//create chunk to write to disk asynck
	Chunk *ch = new Chunk(thisName, thisName, 0, sp->ch->size);
	vector<simgrid::s4u::MailboxPtr>* hosts_to_write = new vector<
			simgrid::s4u::MailboxPtr>();
	hosts_to_write->push_back(Mailbox::by_name(dataNode));
	ch->nodes = hosts_to_write;


	//create spill to add to vector
	spill* direct = new spill();
	direct->ch = ch;
	direct->records = sp->records;
	outDiskV->push_back(direct);


	//add recordes to ctrs
	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, direct->records);
	job->ctr->addToCtr(ctr_t::reduce_spilled_recordes, direct->records);

	job->ctr->addToCtr(ctr_t::reduce_file_bytes_write, sp->ch->size);

	//create asyncwriter actor
	string asyncWrName = thisName + "a_wr_" + to_string(asyncWrId++);
	ActorPtr async_wr = Actor::create(asyncWrName, this_actor::get_host(),
			AsyncWriter(asyncWrName, dataNode, thisName, ch));
	actorPtrV.push_back(async_wr);

}

void Copier::directSpill(spill* sp) {

	double exeFlops = (double) sp->records;
	auto a = this_actor::exec_async(exeFlops);
	pending_comms.push_back(a);

	Chunk* ch = hddmed->writeCh(sp->ch->size);
	spill* direct = new spill();
	direct->ch = ch;
	direct->records = sp->records;
	outDiskV->push_back(direct);

	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, direct->records);

}

void Copier::toDisk() {
	spill* lastsp = outMemV->at(0);
	//XBT_INFO("size is %i   ", lastsp->ch->size);
	for (int i = 1; i < outMemV->size(); i++) {
		lastsp->records += outMemV->at(i)->records;
		lastsp->ch->size += outMemV->at(i)->ch->size;
	}
	//XBT_INFO("size is %i   %i", lastsp->ch->size, outMemV->size());

	int64_t recSize = lastsp->ch->size / lastsp->records;


		double exeFlops = (double) lastsp->records;
		auto a = this_actor::exec_async(exeFlops);
		pending_comms.push_back(a); //tell now we execute one out

		Chunk* ch = hddmed->writeCh(lastsp->ch->size);
		job->ctr->addToCtr(ctr_t::reduce_file_bytes_write, lastsp->ch->size);
		spill* sp = new spill();
		sp->ch = ch;
		sp->records = lastsp->records;
		outMemV->clear();

		outDiskV->push_back(sp);

		job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, sp->records);
		job->ctr->addToCtr(ctr_t::reduce_spilled_recordes, sp->records);


}
string Copier::printMap(map<string, int> rm) {
	string s = "";
	for (auto a : rm) {
		s += "\n" + a.first + "    " + to_string(a.second) + "\n";
	}
	return s;
}
