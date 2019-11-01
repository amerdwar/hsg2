/*
 * AsyncWriter.cpp
 *
 *  Created on: May 13, 2019
 *      Author: alpha
 */

#include "AsyncWriter.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(AsyncWriter, "Messages specific for this example");
AsyncWriter::AsyncWriter(string name,string dataNode,string parent,Chunk* ch){
	this->parent=parent;
	this->thisName=name;
	this->thismb=Mailbox::by_name(thisName);
	this->dataNode=dataNode;
	this->dataNodeMb=Mailbox::by_name(dataNode);
this->ch=ch;
}
void AsyncWriter::operator ()(){
	thismb->set_receiver(Actor::self());
		this->ch->clinetMB = thismb;

		Message *writemsg = new Message(msg_type::cl_dn_wr_ch, thisName, dataNode,
				hdd_Access::hdd_write, ch);

		dataNodeMb->put(writemsg,0);

		Message* ackm = static_cast<Message*>(thismb->get());

		if (ackm->type != msg_type::dn_ack_wr_ch) {
			//XBT_INFO("error write chunk return tag ,AsyncWriter \n %s",ackm->toString().c_str());
			exit(1);
		}



		ch->isWritten=true;



}

AsyncWriter::~AsyncWriter() {
	// TODO Auto-generated destructor stub
}

