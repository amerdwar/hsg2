/*
 * DadaNode.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: alpha
 */

#include "DataNode.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(dataNode, "Messages specific for this example");

DataNode::DataNode(std::vector<std::string> args){
	// TODO Auto-generated constructor stub
mailbox=Mailbox::by_name(this_actor::get_host()->get_name()+"_"+this_actor::get_name());
}
void DataNode::operator()(){
	   simgrid::s4u::CommPtr  comm;
	Message * m=nullptr;
msg_type ty=msg_type::any;
do{

XBT_INFO(" in if ");
	m=static_cast<Message*> (mailbox->get());

switch (m->type){
case msg_type::end_of_simulation :{  break;}
case msg_type::cl_dn_wr_ch :{
	Chunk * ch=static_cast<Chunk*>( m->payload);
	chunks.insert(std::pair<int64_t,Chunk*>(ch->chId,ch));
	ch->writeIndex+=1;
	XBT_INFO("write index size %i  num nodes %i  chunk id %i",ch->writeIndex,ch->nodes->size(),ch->chId);


	if(ch->writeIndex<ch->nodes->size()){
		m->payload=ch;
			m->sender=m->receiver;
			m->receiver=ch->nodes->at(ch->writeIndex)->get_name();

			ch->nodes->at(ch->writeIndex)->put_init(m,ch->size).detach();
			//comm->wait();
	}
	break;
}
}

}while (ty!=msg_type::end_of_simulation);


}
DataNode::~DataNode() {
	// TODO Auto-generated destructor stub
}

