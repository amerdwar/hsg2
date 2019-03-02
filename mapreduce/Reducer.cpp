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
		if(ms->type!=msg_type::map_output_res){
			XBT_INFO("error reducer <msg type");
			exit(1);
		}

		vector<HdfsFile*>* resv = static_cast<vector<HdfsFile*>* >(ms->payload);

	}

	Message* m = nullptr;
	do {
		//sleep and send heart beat to parent
		m = static_cast<Message*>(thismb->get());
		switch (m->type) {
		case msg_type::end_of_simulation: {
			XBT_INFO("reducer manager end of simulation end simulation ");
			break;
		}

		}
	} while (m->type != msg_type::end_of_simulation);

}
Reducer::~Reducer() {
	// TODO Auto-generated destructor stub
}

