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

     nnmb=simgrid::s4u::Mailbox::by_name(nameNode);
     thismb=simgrid::s4u::Mailbox::by_name(simgrid::s4u::this_actor::get_name());
     thismb->set_receiver( Actor::self());

}
  Client:: Client(string arg){


     this->nameNode=arg;
     XBT_INFO("name node is %s",nameNode.c_str());
     nnmb=simgrid::s4u::Mailbox::by_name(nameNode);
     thismb=simgrid::s4u::Mailbox::by_name(simgrid::s4u::this_actor::get_name());
     thismb->set_receiver( Actor::self());

}

void Client::operator ()(){
	HdfsClient* hd=new HdfsClient(nnmb,thismb);
	HdfsFile * h=new HdfsFile(string("d1"),string("f1"),10737418240);
	HdfsFile * h2=new HdfsFile(string("d1"),string("f2"),10737418240);
	auto a=Engine::getClock();
	hd->writeFile(h);
	auto b=Engine::getClock();
	hd->writeFile(h2);
	auto c=Engine::getClock();
hd->read(h);
auto d=Engine::getClock();

double wr1=b-a;
double wr2=c-b;
double re=d-c;
XBT_INFO(" write in %d ",wr1);
XBT_INFO(" write 2 in %d ",wr2);
XBT_INFO(" read in %d ",re);


}
//tell now we have all chunks with the data nodes now we have to send them to data node only
void Client::write(){


	HdfsFile * h=new HdfsFile(string("d1"),string("f1"),10737418240);

	Message *m =new Message(msg_type::cl_nn_wr_file,simgrid::s4u::this_actor::get_name(),nameNode,1,h);
	XBT_INFO("message from client");
	nnmb->put(m,2000);

	Message* m2=static_cast<Message*>( thismb->get());
	XBT_INFO("message from client");
	HdfsFile * f=static_cast<HdfsFile*>( m2->payload);

	for ( int i=0;i<f->chunks->size();i++){


	Message *writemsg =new Message(msg_type::cl_dn_wr_ch,
			simgrid::s4u::this_actor::get_name(),
			f->chunks->at(i)->nodes->at(0)->get_name(),1,f->chunks->at(i));
	f->chunks->at(i)->nodes->at(0)->put(writemsg,f->chunks->at(i)->size);

	//f->chunks->at(i)->nodes->at(0)->put_init(writemsg,f->chunks->at(i)->size)->detach();

	//comm->wait();
	/*
	for(int j=0;j<f->chunks->at(i)->nodes->size();j++){
		XBT_INFO("worker name is %s ",f->chunks->at(i)->nodes->at(j)->get_cname());
		 nnmb=simgrid::s4u::Mailbox::by_name(nameNode);}
	*/
	XBT_INFO("message from client");
	}
for (int i =0;i<f->chunks->size();i++){
	Message* ackm=static_cast<Message*>( thismb->get());
	XBT_INFO("reciecve ack from %s %i",ackm->sender);
	delete ackm;
}//
Message *mack =new Message(msg_type::cl_nn_ack_ch,simgrid::s4u::this_actor::get_name(),nameNode,1,f);
nnmb->put(mack,1024);
XBT_INFO("client send ack");

}

void Client::read(){



	HdfsFile * hr=new HdfsFile(string("d1"),string("f1"),10737418240);
	Message *mr =new Message(msg_type::cl_nn_re_file,simgrid::s4u::this_actor::get_name(),nameNode,1,hr);

	nnmb->put(mr,2000);

	Message* mr2=static_cast<Message*>( thismb->get());
	HdfsFile * fr=static_cast<HdfsFile*>( mr2->payload);
	if(fr->isAck){
	for ( int i=0;i<fr->chunks->size();i++){
	XBT_INFO("ch id %i    num ch is %i ",fr->chunks->at(i)->chId,fr->chunks->size());
	Message *chReq=new Message(msg_type::cl_dn_re_ch,this_actor::get_name()
	,fr->chunks->at(i)->nodes->at(0)->get_name(),1,fr->chunks->at(i));

	//send the request of chunk to data node
	fr->chunks->at(i)->nodes->at(0)->put(chReq,1024);

	//receive the chunk
	Message *mmm=static_cast<Message *>( thismb->get());



	}}
	else{
		XBT_INFO("not ready i will sleep and return");
		//this_actor::sleep_for(1);
		//read();

	}




}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

