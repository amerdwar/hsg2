/*
 * Client.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: alpha
 */

#include "Client.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(hsg, "Messages specific for this example");
  Client:: Client(std::vector<std::string> args){

	 xbt_assert(args.size()>0, "the arguments must be more than one");

this->nameNode=args[1];
thismb=simgrid::s4u::Mailbox::by_name(simgrid::s4u::this_actor::get_name());

//XBT_INFO("this is arg %s ",args[0]);
}
void Client::operator ()(){

	XBT_INFO(" the name node name %s ",nameNode);
	 nnmb=simgrid::s4u::Mailbox::by_name(nameNode);
HdfsFile * h=new HdfsFile(string("d1"),string("f1"),10737418240);

XBT_INFO("di dir didiidid9 %s",h->dir.c_str());


Message *m =new Message(msg_type::cl_nn_wr_file,simgrid::s4u::this_actor::get_name(),nameNode,1,h);
XBT_INFO("before put");
XBT_INFO("  this is the name of mail box %s",nnmb->get_cname());
nnmb->put(m,2000);

Message* m2=static_cast<Message*>( thismb->get());
HdfsFile * f=static_cast<HdfsFile*>( m2->payload);
simgrid::s4u::CommPtr  comm;
for ( int i=0;i<f->chunks->size();i++){
XBT_INFO("ch id %i    num ch is %i ",f->chunks->at(i)->chId,f->chunks->size());

Message *writemsg =new Message(msg_type::cl_dn_wr_ch,
		simgrid::s4u::this_actor::get_name(),
		f->chunks->at(i)->nodes->at(0)->get_name(),1,f->chunks->at(i));

f->chunks->at(i)->nodes->at(0)->put_init(writemsg,f->chunks->at(i)->size)->detach();
//comm->wait();
/*
for(int j=0;j<f->chunks->at(i)->nodes->size();j++){
	XBT_INFO("worker name is %s ",f->chunks->at(i)->nodes->at(j)->get_cname());
	 nnmb=simgrid::s4u::Mailbox::by_name(nameNode);}
*/
}
}
//tell now we have all chunks with the data nodes now we have to send them to data node only


Client::~Client() {
	// TODO Auto-generated destructor stub
}

