/*
 * HdfsClient.cpp
 *
 *  Created on: Jan 9, 2019
 *      Author: alpha
 */

#include "HdfsClient.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(hdfsClient, "Messages specific for this example");

HdfsClient::HdfsClient(simgrid::s4u::MailboxPtr nnmb,
		simgrid::s4u::MailboxPtr thismb) {

	this->nnmb = nnmb;
	this->nameNode = nnmb->get_name();
	this->thismb = thismb;

}
bool HdfsClient::writeFile(HdfsFile *h) {
	std::vector<simgrid::s4u::CommPtr> pending_comms;
	//HdfsFile * h=new HdfsFile(string("d1"),string("f1"),10737418240);
	Message *m = new Message(msg_type::cl_nn_wr_file, thismb->get_name(),
			nameNode, 1, h);
	nnmb->put(m, 1522);
	Message* m2 = static_cast<Message*>(thismb->get());
	HdfsFile * f = static_cast<HdfsFile*>(m2->payload);

	/*	for (int i = 0; i < f->chunks->size(); i++) {
	 for (int j=0;j<f->chunks->at(i)->nodes->size();j++){
	 Chunk *ccc=f->chunks->at(i);
	 XBT_INFO("dir %s  ,file %s chid  %i node %s size%i",ccc->dirName.c_str(),ccc->fileName.c_str(),ccc->chId,f->chunks->at(i)->nodes->at(j)->get_name().c_str(),ccc->size);

	 }

	 }*/

	XBT_INFO("chunks num is %i", f->chunks->size());
	for (int i = 0; i < f->chunks->size(); i++) {

		for (int j = 0; j < f->chunks->at(i)->nodes->size(); j++) {
			Chunk *ccc = f->chunks->at(i);
			XBT_INFO("dir %s  ,file %s chid  %i node %s size %i",
					ccc->dirName.c_str(), ccc->fileName.c_str(), ccc->chId,
					f->chunks->at(i)->nodes->at(j)->get_name().c_str(),
					ccc->size);

		}

		double a = Engine::get_clock();
		Message *writemsg = new Message(msg_type::cl_dn_wr_ch,
				thismb->get_name(), f->chunks->at(i)->nodes->at(0)->get_name(),
				1, f->chunks->at(i));

		//f->chunks->at(i)->nodes->at(0)->put_init(writemsg,1024)->detach();

		f->chunks->at(i)->nodes->at(0)->put(writemsg, f->chunks->at(i)->size);
		Message* ackm = static_cast<Message*>(thismb->get());

			delete ackm;
		double b = Engine::get_clock();

		double c = b - a;

		XBT_INFO("the time %f to send chunk size %i", c,
				f->chunks->at(i)->size);

	}
/*
	for (int i = 0; i < f->chunks->size(); i++) {

		Message* ackm = static_cast<Message*>(thismb->get());

		delete ackm;
	} */
	Message *mack = new Message(msg_type::cl_nn_ack_ch, thismb->get_name(),
			nameNode, 1, f);
	nnmb->put(mack, 1522);

}

bool HdfsClient::read(HdfsFile* hr) {

	//HdfsFile * hr=new HdfsFile(string("d1"),string("f1"),10737418240);
	Message *mr = new Message(msg_type::cl_nn_re_file, thismb->get_name(),
			nameNode, 1, hr);

	nnmb->put(mr, 2000);

	Message* mr2 = static_cast<Message*>(thismb->get());
	HdfsFile * fr = static_cast<HdfsFile*>(mr2->payload);
	if (fr->isAck) {
		for (int i = 0; i < fr->chunks->size(); i++) {

			Message *chReq = new Message(msg_type::cl_dn_re_ch,
					thismb->get_name(),
					fr->chunks->at(i)->nodes->at(0)->get_name(), 1,
					fr->chunks->at(i));

			//send the request of chunk to data node
			fr->chunks->at(i)->nodes->at(0)->put(chReq, 1024);

			//receive the chunk
			Message *mmm = static_cast<Message *>(thismb->get());

		}
	} else {
		XBT_INFO("not ready i will sleep and return");
		//this_actor::sleep_for(1);
		//read();

	}

}

HdfsClient::~HdfsClient() {
	// TODO Auto-generated destructor stub
}

