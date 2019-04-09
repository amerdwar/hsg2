/*
 * Reducer.cpp
 *
 *  Created on: Mar 1, 2019
 *      Author: alpha
 */

#include "Reducer.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Reducer, "Messages specific for this example");
Reducer::Reducer(string thisName, string appMas, string NameNode,
		string dataNodeName, allocateRes * res) {
	coName = "";
	inputs = new vector<spill*>();
	inputsMem = new vector<spill*>();
	this->rid = reduceIds++;
	this->dataNodeName = dataNodeName;
	this->thisName = thisName;
	this->appMasterName = appMas;
	this->nameNodeName = NameNode;
	this->res = res;
	nodeManagerName = res->nodeManager;
	nodeManagerMb = Mailbox::by_name(nodeManagerName);
	this->job = res->job;
	nnmb = Mailbox::by_name(nameNodeName);
	hddm = new HddMediator(dataNodeName, thisName, thisName);
	dataNodeMb = Mailbox::by_name(dataNodeName);
	appMasterMb = Mailbox::by_name(appMasterName);
	thismb = Mailbox::by_name(thisName);
	outputf = new HdfsFile(thisName, thisName, 0);

	XBT_INFO("create reduce task");

}
void Reducer::operator()() {
	thismb->set_receiver(Actor::self());

	Message *mapOutReqMsg = new Message(msg_type::map_output_req, thisName,
			appMasterName, 0, nullptr);

	appMasterMb->put(mapOutReqMsg, 1522);

	int copiers = job->mapReduceParallelCopies;
	coName = thisName + "_co";
	ActorPtr copier = Actor::create(coName, this_actor::get_host(),
			Copier(coName, thisName, copiers, job, dataNodeName));

	copyOutPut(); //here we copy output using copier <the out put is in inputs vector
	exeReduce();

	XBT_INFO(printMapOut(inputs).c_str());
	XBT_INFO(printMapOut(inputsMem).c_str());

	HddMediator *hdtem = new HddMediator(dataNodeName, thisName, thisName);
	XBT_INFO("berfore write output to hdfs");
	hdtem->writeCh(200 * 1024);

	XBT_INFO("after write output to hdfs");

	Message* finishMsg = new Message(msg_type::reducer_finish, thisName,
			appMasterName, 0, nullptr);

	XBT_INFO("before send finish");
	appMasterMb->put(finishMsg, 1522);

	Message * finishMsg2 = new Message(msg_type::reducer_finish, thisName,
			nodeManagerName, 0, nullptr);
	nodeManagerMb->put(finishMsg2, 1522);
	XBT_INFO("after send finish");

}
Reducer::~Reducer() {
	// TODO Auto-generated destructor stub
}
int64_t Reducer::reduceIds = 0;
void Reducer::copyOutPut() {

	while (true) {
		Message* m = static_cast<Message*>(thismb->get());

		vector<spill*>* payload = static_cast<vector<spill*>*>(m->payload);
		XBT_INFO("get payload");

		if (sendMapToCopier(payload)) {


			break;
		}

	}
	Message *finishMsg = new Message(msg_type::finish_copier, this->thisName,
			coName, 0, nullptr);

	Mailbox::by_name(coName)->put(finishMsg, 0);

	Message* outMsg = static_cast<Message*>(thismb->get());
	if (outMsg->type != msg_type::finish_copier) {
		XBT_INFO("error return type no finish copier");
		exit(0);
	}

	inputsMem = static_cast<vector<spill*>*>(outMsg->payload);
	Message* outMsg2 = static_cast<Message*>(thismb->get());
	if (outMsg2->type != msg_type::finish_copier) {
		XBT_INFO("m is   %s",outMsg2->toString().c_str());
		XBT_INFO("error return type no finish copier2 %i",outMsg2->type );
		exit(0);
	}

	inputs = static_cast<vector<spill*>*>(outMsg2->payload);


}

bool Reducer::sendMapToCopier(vector<spill*>* payload) {
	XBT_INFO("in send map to co%i", payload->size());
	bool isLast = false;
	vector<spill*>* payV=new vector<spill*>();
	for (int j = 0; j < payload->size(); j++) {
		if (!payload->at(j)->isLast) {
			//inputs->push_back(payload->at(j));
			payV->push_back(payload->at(j));
			reqNum++;
		} else {
			isLast = true;
			XBT_INFO("this is the last spill");
		}

	}
	Message *chReadReq = new Message(msg_type::cl_dn_re_ch,
						this->thisName, coName, hdd_Access::hdd_read,
						payV);
				Mailbox::by_name(coName)->put(chReadReq, 0);
//here we send vector of spill
	return isLast;
}

string Reducer::printSpill(spill* sp) {
	string s = "";
	if (!sp->isLast) {
		s += "spill size is " + to_string(sp->ch->size);
		s += "num rec  is " + to_string(sp->records);
		s += "is last  one  " + to_string(sp->isLast);
	} else
		s += "this finish spill ";
	return s;
}

string Reducer::printMapOut(vector<spill*>* a) {

	string s = "this is the output of job  \n";

	for (int i = 0; i < a->size(); i++) {

		s += printSpill(a->at(i)) + "\n";

	}

	s += "\n";
	return s;
}

void Reducer::exeReduce() {
//TODO merge all files to single file then



}
