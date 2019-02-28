/*
 * AppMaster.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: alpha
 */

#include "AppMaster.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(AppMaster, "Messages specific for this example");
AppMaster::AppMaster(JobInfo* j, string parent, string self, string namenode,
		string rManager) {
	this->parent = parent;
	this->job = j;
	this->self = self;
	this->nameNode = namenode;
	this->rManager = rManager;
	parentMb = Mailbox::by_name(parent);
	nameNodeMb = Mailbox::by_name(namenode);
	rManagerMb = Mailbox::by_name(rManager);
	thisMb = Mailbox::by_name(self);
	XBT_INFO("create app master for job name:%s",job->jobName.c_str());
}

void AppMaster::operator ()() {

	thisMb->set_receiver(Actor::self());
	XBT_INFO("in operator app master");
	sendMapRequest();

	Message* m = nullptr;
	do {
		m = static_cast<Message*>(thisMb->get());
		switch (m->type) {
		case msg_type::end_of_simulation: {
			XBT_INFO("resource manager end of simulation end simulation ");
			break;
		}
		case msg_type::allocate_res: {
			allocateRes* res = static_cast<allocateRes*>(m->payload);
			sendAllocationFromAppMasterToNodeManager(res); //send allocation res to node manager to create maper or reducers
			break;
		}
		case msg_type::heart_beat: {
//TODO send update reports
			break;
		}

		}
	} while (m->type != msg_type::end_of_simulation);

}

AppMaster::~AppMaster() {
	// TODO Auto-generated destructor stub
}

void AppMaster::sendMapRequest() {

	allocateReq* mapReq=new allocateReq;
	mapReq->type = allocate_type::map_all;
	mapReq->dir = job->dir;
	mapReq->job = job;
	mapReq->requester = self;
	Message* mapReqMsg = new Message(msg_type::allocate_req, self, rManager, 0,
			mapReq);
	XBT_INFO("before send map req");
	rManagerMb->put(mapReqMsg, 1522);
	XBT_INFO("after send map req");
}
void AppMaster::sendAllocationFromAppMasterToNodeManager(allocateRes* res) {
	res->requester = self;
	Message* mapResMsg = new Message(msg_type::allocate_res, self,
			res->nodeManager, 0, res);
	MailboxPtr nMan = Mailbox::by_name(res->nodeManager);
	nMan->put(mapResMsg, 1522);

}
