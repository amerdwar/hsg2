/*
 * HddMediator.cpp
 *
 *  Created on: Feb 25, 2019
 *      Author: alpha
 */

#include "HddMediator.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(hddMediator, "Messages specific for this example");
HddMediator::HddMediator(string dataNodeName, string sender, string task) {

	this->task = task;
	this->sender = sender;
	this->thismb = Mailbox::by_name(sender);

	this->dataNodeName = dataNodeName;
	this->dataNode = Mailbox::by_name(dataNodeName);
	freeCopiers = parallelCopiers;

}

HddMediator::~HddMediator() {
	// TODO Auto-generated destructor stub
}

Chunk* HddMediator::writeCh(int64_t size) {
	Chunk *ch = new Chunk(task, task, 0, size);
	ch->clinetMB = thismb;
	vector<simgrid::s4u::MailboxPtr>* hosts_to_write = new vector<
			simgrid::s4u::MailboxPtr>();
	hosts_to_write->push_back(dataNode);
	ch->nodes = hosts_to_write;

	Message *writemsg = new Message(msg_type::cl_dn_wr_ch, sender, dataNodeName,
			hdd_Access::hdd_write, ch);


	dataNode->put(writemsg, size);

	Message* ackm = static_cast<Message*>(thismb->get());

	if (ackm->type != msg_type::dn_ack_wr_ch) {
		XBT_INFO("error write chunk return tag ,hddmediator \n %s",ackm->toString().c_str());
		exit(1);
	}

	ch->isWritten=true;
	return ch;
}
void HddMediator::readCh(Chunk* ch) {
	Message *chReq = new Message(msg_type::cl_dn_re_ch, thismb->get_name(),
			dataNodeName, hdd_Access::hdd_read, ch);

	//send the request of chunk to data node
	dataNode->put(chReq, 1522);
	//receive the ack

	Message *mmm = static_cast<Message *>(thismb->get());
	XBT_INFO("mapper read chunk finished");
	if (mmm->type != msg_type::dn_cl_re_ack_ch) {
		XBT_INFO("error read chunk hdd mediator <type mismatch");
		exit(1);
	}

}


void HddMediator::deleteCh(Chunk* ch) {
	Message *chReq = new Message(msg_type::cl_dn_del_ch, thismb->get_name(),
			dataNodeName, 0, ch);
	//send the request of chunk to data node
	dataNode->put(chReq, 1522);
	XBT_INFO("sssssssssssssssssss, %s",thismb->get_name().c_str());
	chReq=static_cast<Message*>(thismb->get());
	XBT_INFO("dddddkkkkkddddddddddddddd, %i",ch->chGenId);
	if (chReq->type != msg_type::cl_dn_del_ch_ack) {
			XBT_INFO("error delete return type");
			exit(1);
		}



}

