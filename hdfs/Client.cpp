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
	//XBT_INFO("name node is %s", nameNode.c_str());
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
	ofstream myfile;
	double firstd = Engine::get_clock();
	myfile.open("write.txt");
	int smallSize = 367001; //this is 0.35 mb in bytes
	int bigSize = 3195759; //this is 3 mb in bytes
	int allSize = 335544320;
	vector<double> med;
	int64_t ss;
	for (int i = 1; i < 2; i++) {
		if(i<40)
			ss = smallSize * (double) i;
			else
		ss += bigSize;

		vector<double> all;
		double median;
		for (int j = 1; j < 52; j++) {
			HdfsFile * h = new HdfsFile(std::to_string(i), std::to_string(j),
					ss);
			double a = Engine::get_clock();
			hd->writeFile(h);
			double b = Engine::get_clock();
			double c = b - a;

			all.push_back(c);
		}
		sort(all.begin(), all.end());
		median = all.at(25);
		all.clear();
		double sizeInMB = ((double) ss) / (1024 * 1024);
		double throughput = sizeInMB / median;

		myfile
				<< boost::format("throughput tt=%1%  s=%2% is t=%3%") % median
						% throughput % sizeInMB << "\n";
	}
	int temp = 0;

	myfile.close();
	double secondd = Engine::get_clock();
	//XBT_INFO("finish simulation in %f ", secondd - firstd);

	this->read();

	Message *ends = new Message(msg_type::end_of_simulation,
			simgrid::s4u::this_actor::get_name(),
		nameNode,0,nullptr);
	nnmb->put (ends,1522);
	//XBT_INFO("client end simulatoin");


}
//tell now we have all chunks with the data nodes now we have to send them to data node only
void Client::write() {

	HdfsFile * h = new HdfsFile(string("d1"), string("f1"), 10737418240);

	Message *m = new Message(msg_type::cl_nn_wr_file,
			simgrid::s4u::this_actor::get_name(), nameNode, 0, h);

	nnmb->put(m, 2000);

	Message* m2 = static_cast<Message*>(thismb->get());

	HdfsFile * f = static_cast<HdfsFile*>(m2->payload);

	for (int i = 0; i < f->chunks->size(); i++) {

		Message *writemsg = new Message(msg_type::cl_dn_wr_ch,
				simgrid::s4u::this_actor::get_name(),
				f->chunks->at(i)->nodes->at(0)->get_name(), 0,
				f->chunks->at(i));
		f->chunks->at(i)->nodes->at(0)->put(writemsg, f->chunks->at(i)->size);

		//f->chunks->at(i)->nodes->at(0)->put_init(writemsg,f->chunks->at(i)->size)->detach();

		//comm->wait();
		/*
		 for(int j=0;j<f->chunks->at(i)->nodes->size();j++){
		 //XBT_INFO("worker name is %s ",f->chunks->at(i)->nodes->at(j)->get_cname());
		 nnmb=simgrid::s4u::Mailbox::by_name(nameNode);}
		 */

	}
	for (int i = 0; i < f->chunks->size(); i++) {
		Message* ackm = static_cast<Message*>(thismb->get());

		delete ackm;
	} //
	Message *mack = new Message(msg_type::cl_nn_ack_ch,
			simgrid::s4u::this_actor::get_name(), nameNode, 0, f);
	nnmb->put(mack, 1024);


	this->read();
//end simulation so end name node --->end data nodes --> end hdd

}

void Client::read() {


	HdfsClient* hd = new HdfsClient(nnmb, thismb);
	ofstream myfile;
		double firstd = Engine::get_clock();
		myfile.open("read.txt");
		int smallSize = 367001; //this is 0.35 mb in bytes
		int bigSize = 3195759; //this is 3 mb in bytes
		int allSize = 335544320;
		vector<double> med;
		int64_t ss;
		for (int i = 1; i < 2; i++) {
			if(i<40)
				ss = smallSize * (double) i;
				else
			ss += bigSize;

			vector<double> all;
			double median;
			for (int j = 1; j < 52; j++) {
				HdfsFile * h = new HdfsFile(std::to_string(i), std::to_string(j),
						ss);
				double a = Engine::get_clock();
				hd->read(h);
				double b = Engine::get_clock();
				double c = b - a;

				all.push_back(c);
			}
			sort(all.begin(), all.end());
			median = all.at(25);
			all.clear();
			double sizeInMB = ((double) ss) / (1024 * 1024);
			double throughput = sizeInMB / median;

			myfile
					<< boost::format("throughput tt=%1%  s=%2% is t=%3%") % median
							% throughput % sizeInMB << "\n";
		}
		int temp = 0;

		myfile.close();
		double secondd = Engine::get_clock();
		//XBT_INFO("finish read simulation in %f ", secondd - firstd);



}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

