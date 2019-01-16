/*
 * Client.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: alpha
 */

#include "Client.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(hsg, "Messages specific for this example");
Client::Client(std::vector<std::string> args) {

	xbt_assert(args.size() > 0, "the arguments must be more than one");
	this->nameNode = args[1];
	this->f1 = args[2];
	this->f2 = args[3];
	nnmb = simgrid::s4u::Mailbox::by_name(nameNode);
	thismb = simgrid::s4u::Mailbox::by_name(
			simgrid::s4u::this_actor::get_host()->get_name() + "_"
					+ simgrid::s4u::this_actor::get_name());
	thismb->set_receiver(Actor::self());

}
Client::Client(string arg) {

	this->nameNode = arg;
	XBT_INFO("name node is %s", nameNode.c_str());
	nnmb = simgrid::s4u::Mailbox::by_name(nameNode);
	thismb = simgrid::s4u::Mailbox::by_name(
			simgrid::s4u::this_actor::get_host()->get_name() + "_"
					+ simgrid::s4u::this_actor::get_name());
	thismb->set_receiver(Actor::self());

}

void Client::operator ()() {
	HdfsClient* hd = new HdfsClient(nnmb, thismb);
//	HdfsFile * h = new HdfsFile(string("d1"), this->f1, 10737418240);
	//HdfsFile * h2 = new HdfsFile(string("d1"), this->f2, 10737418240);

//	hd->read(h);

//write 78 dataset  files from 0.25 mb to 320 mb each data set contains 500 file with the same size

	int smallSize = 367001; //this is 0.35 mb in bytes
	int bigSize = 3145728; //this is 3 mb in bytes
	double all[78];
	for (int i = 1; i < 40; i++) {
		//start from 0.25 and increment with 0.35
		vector<double>  medians;
		int64_t ss=smallSize	 * i;
		for (int j = 1; j < 501; j++) {

			HdfsFile * h = new HdfsFile(std::to_string(i), std::to_string(j),
					ss);
			double a = Engine::get_clock();
			hd->writeFile(h);
			double b = Engine::get_clock();
			medians.push_back(b-a);

		}
	sort(medians.begin(),medians.end());
all[i]=(medians.at(249)+medians.at(250))/2;
XBT_INFO("the time to write s=%i is t=%g",ss,all[i]);
	}
	for (int i = 78; i > 39; i--) {
		//start from 320 and decrease with 3
		vector<double>  medians;
		int64_t ss=bigSize	 * i;
		for (int j = 1; j < 501; j++) {

			HdfsFile * h = new HdfsFile(std::to_string(i), std::to_string(j),
	ss	);
			double a = Engine::get_clock();
			hd->writeFile(h);
			double b = Engine::get_clock();
			medians.push_back(b-a);

		}
	sort(medians.begin(),medians.end());
all[i]=(medians.at(249)+medians.at(250))/2;
XBT_INFO("the time to write s=%i is t=%g",ss,all[i]);
	}

	//   0.25    0.25
	//   0.35     0.6
	//   0.4       0.65
	//5   0.45      0.7
	//5   0.5       0.75
	//    1.25      2
	//    1.5        3.5
	//    2          5.5
	//     3         8.5
	//      3.5      12
	//       5

}
//tell now we have all chunks with the data nodes now we have to send them to data node only
void Client::write() {

	HdfsFile * h = new HdfsFile(string("d1"), string("f1"), 10737418240);

	Message *m = new Message(msg_type::cl_nn_wr_file,
			simgrid::s4u::this_actor::get_name(), nameNode, 1, h);

	nnmb->put(m, 2000);

	Message* m2 = static_cast<Message*>(thismb->get());

	HdfsFile * f = static_cast<HdfsFile*>(m2->payload);

	for (int i = 0; i < f->chunks->size(); i++) {

		Message *writemsg = new Message(msg_type::cl_dn_wr_ch,
				simgrid::s4u::this_actor::get_name(),
				f->chunks->at(i)->nodes->at(0)->get_name(), 1,
				f->chunks->at(i));
		f->chunks->at(i)->nodes->at(0)->put(writemsg, f->chunks->at(i)->size);

		//f->chunks->at(i)->nodes->at(0)->put_init(writemsg,f->chunks->at(i)->size)->detach();

		//comm->wait();
		/*
		 for(int j=0;j<f->chunks->at(i)->nodes->size();j++){
		 XBT_INFO("worker name is %s ",f->chunks->at(i)->nodes->at(j)->get_cname());
		 nnmb=simgrid::s4u::Mailbox::by_name(nameNode);}
		 */

	}
	for (int i = 0; i < f->chunks->size(); i++) {
		Message* ackm = static_cast<Message*>(thismb->get());

		delete ackm;
	} //
	Message *mack = new Message(msg_type::cl_nn_ack_ch,
			simgrid::s4u::this_actor::get_name(), nameNode, 1, f);
	nnmb->put(mack, 1024);


}

void Client::read() {

	HdfsFile * hr = new HdfsFile(string("d1"), string("f1"), 10737418240);
	Message *mr = new Message(msg_type::cl_nn_re_file,
			simgrid::s4u::this_actor::get_name(), nameNode, 1, hr);

	nnmb->put(mr, 2000);

	Message* mr2 = static_cast<Message*>(thismb->get());
	HdfsFile * fr = static_cast<HdfsFile*>(mr2->payload);
	if (fr->isAck) {
		for (int i = 0; i < fr->chunks->size(); i++) {
			XBT_INFO("ch id %i    num ch is %i ", fr->chunks->at(i)->chId,
					fr->chunks->size());
			Message *chReq = new Message(msg_type::cl_dn_re_ch,
					this_actor::get_name(),
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

Client::~Client() {
	// TODO Auto-generated destructor stub
}

