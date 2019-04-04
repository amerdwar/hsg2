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
	q = new queue<Message*>();
	this->nCopiers = nCopiers;
	this->nFreeCopiers = nCopiers;
	this->parent = parent;
	this->thisName = thisName;
	this->dataNode = datNodeName;
this->memBytes=int64_t(job->memoryLimit*job->mapredJobShuffleMergePercent);
	merger = new Combiner(job, dataNode, thisName);
	thismb = Mailbox::by_name(thisName);
	parentMb = Mailbox::by_name(parent);

}

void Copier::operator()() {
	int reqNum = 0;
	int ackNum = 0;

	thismb->set_receiver(Actor::self());

	Message* m = nullptr;
	bool isFinish = false;
	do {

		m = static_cast<Message*>(thismb->get());
		XBT_INFO("in copier");
		switch (m->type) {

		case msg_type::finish_copier: {
			XBT_INFO("copier  finish ");
			isFinish = true;
			//send finish to parent
			break;
		}
		case msg_type::cl_dn_re_ch: {
			XBT_INFO("in copier");
			exe(m);
			reqNum++;
			if (nFreeCopiers > 0) {
				sendReadReg(m);
				nFreeCopiers--;
			} else {
				q->push(m);

			}
			break;
		}
		case msg_type::dn_cl_re_ack_ch: {

			ackNum++;
			if (q->size() > 0) {
				sendReadReg(q->front());
				q->pop();
			} else {
				nFreeCopiers++;
			}

			break;
		}

		}
		if (isFinish && ackNum == reqNum) {
			XBT_INFO("end copier %i ,%i  ,%i", isFinish, ackNum, reqNum);
			break;
		}
	} while (true);

}

Copier::~Copier() {
	// TODO Auto-generated destructor stub
}

void Copier::sendReadReg(Message *m) {

	spill* sp = static_cast<spill*>(m->payload);
	MailboxPtr dnmb = sp->ch->nodes->at(0);
	string dn = dnmb->get_name();

	Message *chReq = new Message(msg_type::cl_dn_re_ch, this->thisName, dn,
			hdd_Access::hdd_read, sp->ch);
	//send the request of chunk to data node
	dnmb->put(chReq, 1522);

	//ExecPtr exep=this_actor::exec_async(ch->size);

}

spill* Copier::exe(Message* m) { //execute the
	spill* sp = static_cast<spill*>(m->payload);
	Chunk * ch = sp->ch;
	int recNum = sp->records;
//exe for merge
//if(compiner) exe and new size will be
//thene write to this data node
	double exeFlops = (double) recNum;
	int64_t lastRecNum = merger->combine(recNum);
	int64_t lastSize;
	if (lastRecNum == recNum) {
		lastSize = ch->size;
		exeFlops += (double) job->combineCost * recNum;
		//XBT_INFO("no compiiner so size is %i", lastSize);
	} else {
		lastSize = lastRecNum * job->combineOutAvRecordSize;
		//XBT_INFO("yes compiiner so size is %i", lastSize);
	}
	auto a = this_actor::exec_async(exeFlops);
	pending_comms.push_back(a); //tell now we execute one out

	ch->size = lastSize;
	sp->records = lastRecNum;

	return sp;
}

void Copier::writeSpill(spill* sp){
int64_t chSize=sp->ch->size;
if(memBytes>0){
if(memBytes>chSize){
	memBytes-=chSize;
	sp->isInMem=true;
	//to do push to spills vector
}
	else{
		int recSize=chSize/sp->records;

		int64_t memChSize=memBytes;//write in to memory
		chSize-=memBytes;//the remender to write to hard
		memBytes=0;//all memory bytes are used so there is not free memory
		//split the spill in to memory chunk and hdd chunk
		sp->ch->size=chSize;
		sp->records=chSize/recSize;
//write sp and add to vector

//create memory spill
		spill* memSp=new spill();
		Chunk* memCh=new Chunk(parent,parent,0,memChSize);
		memSp->ch=memCh;
		memSp->records=memChSize/recSize;
		memSp->isInMem=true;
		//TODO add to vector


	}

}else{

	//TODO write spill and push it to vector
}
}
