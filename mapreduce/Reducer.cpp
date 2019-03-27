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
	while (true) {
		Message* ms = static_cast<Message*>(thismb->get());
		if (ms->type != msg_type::map_output_res) {
			XBT_INFO("error reducer <msg type");
			exit(1);
		}

		vector<spill*>* resv = static_cast<vector<spill*>*>(ms->payload);
		for (int i = 0; i < resv->size(); i++) {
			inputs->push_back(resv->at(i));

		}
		if (inputs->size() == job->numberOfMappers) {
			XBT_INFO(" get all map outputs go %i", inputs->size());
			break;
		}
	}
	for (int i = 0; i < inputs->size(); i++) {

		string temNodeMan =
				inputs->at(i)->chunks->at(0)->nodes->at(0)->get_name();

		HddMediator *hdtem = new HddMediator(temNodeMan, thisName, thisName);
		for (int k = 0; k < inputs->at(i)->chunks->size(); k++) {

			XBT_INFO("before read chunk %s  %s",inputs->at(i)->name.c_str(),thisName.c_str());
			hdtem->readCh(inputs->at(i)->chunks->at(k));
			XBT_INFO("after rea  %i  %i",i,k);
		}
	}

	HddMediator *hdtem = new HddMediator(dataNodeName, thisName, thisName);
	XBT_INFO("berfore write output to hdfs");
	hdtem->writeCh(200*1024);

	XBT_INFO("after write output to hdfs");


	Message* finishMsg = new Message(msg_type::reducer_finish, thisName,
			appMasterName, 0, nullptr);

	XBT_INFO("before send finish");
	appMasterMb->put(finishMsg, 1522);

Message * finishMsg2=new Message(msg_type::reducer_finish, thisName,nodeManagerName, 0, nullptr);
nodeManagerMb->put(finishMsg2,1522);
	XBT_INFO("after send finish");




}
Reducer::~Reducer() {
	// TODO Auto-generated destructor stub
}
int64_t Reducer::reduceIds = 0;
