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
	numAllReducers = j->numberOfReducers;
	for (auto it = j->dir->Files->begin(); it != j->dir->Files->end(); it++) {

		for (int i = 0; i < it->second->chunks->size(); i++) {
			numAllMappers++;

		}
	}
	XBT_INFO("num all mappers %i", numAllMappers);
	numFinishedMappers = numFinishedReducers = 0;
	this->job->numberOfMappers = numAllMappers;
	this->self = self;
	this->nameNode = namenode;
	this->rManager = rManager;
	nodeManager = self.substr(0, self.find('_'));
	nodeManagerMb = Mailbox::by_name(nodeManager);
	parentMb = Mailbox::by_name(parent);
	nameNodeMb = Mailbox::by_name(namenode);
	rManagerMb = Mailbox::by_name(rManager);
	thisMb = Mailbox::by_name(self);
	XBT_INFO("create app master for job name:%s", job->jobName.c_str());
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
		case msg_type::map_finish: {
			mapFinished(m);

			break;
		}
		case msg_type::reducer_finish: {
			bool res = reduceFinished(m);
			if (res)
				goto end;
			break;
		}
		case msg_type::map_output_req: {
			sendOutTellNow(m->sender);
			break;
		}

		}
	} while (m->type != msg_type::end_of_simulation);
	end: XBT_INFO("all reducers finished");
}

AppMaster::~AppMaster() {
	// TODO Auto-generated destructor stub
}

void AppMaster::sendMapRequest() {

	allocateReq* mapReq = new allocateReq;
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
void AppMaster::sendReduceRequest() {

	allocateReq* reduceReq = new allocateReq;
	reduceReq->type = allocate_type::reduce_all;
	reduceReq->reducersNum = job->numberOfReducers;
	reduceReq->dir = job->dir;
	reduceReq->job = job;
	reduceReq->requester = self;
	Message* mapReqMsg = new Message(msg_type::allocate_req, self, rManager, 0,
			reduceReq);
	XBT_INFO("before send reduce req mas");
	rManagerMb->put(mapReqMsg, 1522);
	XBT_INFO("after send reduce req mas");
}
void AppMaster::sendAllocationFromAppMasterToNodeManager(allocateRes* res) {
	res->requester = self;
	Message* mapResMsg = new Message(msg_type::allocate_res, self,
			res->nodeManager, 0, res);
	MailboxPtr nMan = Mailbox::by_name(res->nodeManager);
	nMan->put(mapResMsg, 1522);

	//the map name is m_jobid_fileindex_chunkIndex
	if (res->type == allocate_type::map_all) {
		string mapName = res->nodeManager + "_m_" + to_string(res->job->jid)
				+ "_" + to_string(res->fIndex) + "_" + to_string(res->chIndex);
		mappers.push_back(mapName);
	} else {
//wait to get map out put request and then add it to reducers
	}

}
void AppMaster::requestReducers() {
	if (!reduceReqIsSent) {
		double d = ((double) numFinishedMappers / (double) numAllMappers)
				* 100.0;
		if (d > 5.0) {
			sendReduceRequest();
			reduceReqIsSent = true;
		}

	}
}
void AppMaster::freeContainer(string* con) {

	Message* freeConMsg = new Message(msg_type::free_con, self, rManager, 0,
			con);

	rManagerMb->put(freeConMsg, 1522);

}
void AppMaster::sendOutTellNow(string reducer) {
	vector<HdfsFile*>* outRes = new vector<HdfsFile*>();
	if (mapOutV.size() > 0) {
		for (auto a : mapOutV) {
			outRes->push_back(a);

		}
	}
	reducers.push_back(reducer);
	Message* outResMsg = new Message(msg_type::map_output_res, self, reducer, 0,
			outRes);

	Mailbox::by_name(reducer)->put(outResMsg, 1522);

}
void AppMaster::mapFinished(Message * m) {

	this->numFinishedMappers++;
	requestReducers();
	HdfsFile* res = static_cast<HdfsFile*>(m->payload);
	mapOutV.push_back(res);

	//free map container
	string s = m->sender.substr(0, m->sender.find('_'));

	string* mm = new string;
	*mm = s;
	freeContainer(mm);

	//send out put to all available reducers
	for (auto a : reducers) {

		vector<HdfsFile*>* outRes = new vector<HdfsFile*>();
		outRes->push_back(res);
		Message* outResMsg = new Message(msg_type::map_output_res, self, a, 0,
				outRes);
		Mailbox::by_name(a)->put(outResMsg, 1522);

	}

}
bool AppMaster::reduceFinished(Message *m) {
	bool isFinished = false;
	this->numFinishedReducers++;
	//free map container
	string s = m->sender.substr(0, m->sender.find('_'));
	string* mm = new string;
	*mm = s;
	freeContainer(mm);
	if (numFinishedReducers == numAllReducers) {
		XBT_INFO("this is the last reducer send finish back");
		string st = m->sender.substr(0, self.find('_'));
		string* mmm = new string;
		*mmm = s;
		freeContainer(mmm);
		//to do send finish to node manager

		Message * finishMsg2 = new Message(msg_type::reducer_finish, self,
				nodeManager, 0, nullptr);
		nodeManagerMb->put(finishMsg2, 1522);


		Message * finishMsg3 = new Message(msg_type::finish_job, self,
					rManager, 0, job);
			rManagerMb->put(finishMsg3, 1522);


		XBT_INFO("after send reduce finish");

		isFinished = true;
	}
	return isFinished;
}
