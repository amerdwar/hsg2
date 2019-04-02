/*
 * Copier.cpp
 *
 *  Created on: Mar 30, 2019
 *      Author: alpha
 */

#include "Copier.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Copier, "Messages specific for this example");
Copier::Copier(string thisName, string parent, int nCopiers,JobInfo* job) {
	this->job=job;
	q = new queue<Message*>();
	this->nCopiers = nCopiers;
	this->nFreeCopiers = nCopiers;
	this->parent = parent;
	this->thisName = thisName;

	thismb = Mailbox::by_name(thisName);
	parentMb = Mailbox::by_name(parent);

}

void Copier::operator()() {
int reqNum=0;
int ackNum=0;

	thismb->set_receiver(Actor::self());

	Message* m = nullptr;
	bool isFinish=false;


	do {

		m = static_cast<Message*>(thismb->get());
		XBT_INFO("in copier");
		switch (m->type) {
		case msg_type::finish_copier: {
			XBT_INFO("copier  finish ");
			isFinish=true;
			//send finish to parent
			break;
		}
		case msg_type::cl_dn_re_ch: {
			XBT_INFO("in copier");
reqNum++;
			if (nFreeCopiers > 0) {
				sendReadReg(m);
			} else {
				q->push(m);

			}
			break;
		}
		case msg_type::dn_cl_re_ack_ch: {
			XBT_INFO("get ach from data node");
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
		if(isFinish && ackNum==reqNum){
			XBT_INFO("end copier %i ,%i  ,%i",isFinish,ackNum,reqNum);
			break;
		}
	} while (true);

}

Copier::~Copier() {
	// TODO Auto-generated destructor stub
}

void Copier::sendReadReg(Message *m) {

	Chunk* ch = static_cast<Chunk*>(m->payload);
	MailboxPtr dnmb = ch->nodes->at(0);
	string dn=dnmb->get_name();

	Message *chReq = new Message(msg_type::cl_dn_re_ch, this->thisName, dn,
			hdd_Access::hdd_read, ch);
	//send the request of chunk to data node
	dnmb->put(chReq, 1522);
}
