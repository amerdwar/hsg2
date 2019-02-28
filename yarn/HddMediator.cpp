/*
 * HddMediator.cpp
 *
 *  Created on: Feb 25, 2019
 *      Author: alpha
 */

#include "HddMediator.h"

HddMediator::HddMediator(string dataNodeName, string sender, string task) {

	this->task = task;
	this->sender = sender;
	this->thismb = Mailbox::by_name(sender);
	this->dataNodeName = dataNodeName;
	this->dataNode = Mailbox::by_name(dataNodeName);
}

HddMediator::~HddMediator() {
	// TODO Auto-generated destructor stub
}

Chunk* HddMediator::writeCh(int64_t size) {
	Chunk *ch = new Chunk(task, task, 0, size);
	ch->clinetMB = sender;
	vector<simgrid::s4u::MailboxPtr>* hosts_to_write = new vector<
			simgrid::s4u::MailboxPtr>();
	hosts_to_write->push_back(dataNode);
	ch->nodes = hosts_to_write;

	Message *writemsg = new Message(msg_type::cl_dn_wr_ch, sender, dataNodeName,
			0, ch);
	//f->chunks->at(i)->nodes->at(0)->put_init(writemsg,1024)->detach();
	dataNode->put(writemsg, size);
	Message* ackm = static_cast<Message*>(thismb->get());

	if (ackm->type != msg_type::dn_ack_wr_ch)
		exit(1);
	return ch;
}
void HddMediator::readCh(Chunk*  ch) {
	Message *chReq = new Message(msg_type::cl_dn_re_ch, thismb->get_name(),
			dataNodeName, 0, ch);

	//send the request of chunk to data node
	dataNode->put(chReq, 1522);

	//receive the ack
	Message *mmm = static_cast<Message *>(thismb->get());
}
void HddMediator::deleteCh(Chunk* ch){
	Message *chReq = new Message(msg_type::cl_dn_del_ch, thismb->get_name(),
				dataNodeName, 0, ch);

		//send the request of chunk to data node
		dataNode->put(chReq, 1522);
}
