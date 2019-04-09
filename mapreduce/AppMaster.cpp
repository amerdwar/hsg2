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
	//XBT_INFO("num all mappers %i", numAllMappers);
	numFinishedMappers = numFinishedReducers = 0;
	this->job->numberOfMappers = numAllMappers;
	this->self = self;
	this->nameNode = namenode;
	this->rManager = rManager;
	nodeManager = parent;
	nodeManagerMb = Mailbox::by_name(nodeManager);
	parentMb = Mailbox::by_name(parent);
	nameNodeMb = Mailbox::by_name(namenode);
	rManagerMb = Mailbox::by_name(rManager);
	thisMb = Mailbox::by_name(self);
	XBT_INFO("create app master for job name:%s", job->jobName.c_str());
	mapOutV = new map<int, vector<spill*>*>();
	for (int i = 0; i < job->numberOfReducers; i++) {
		vector<spill*>* t = new vector<spill*>();
		mapOutV->insert(std::pair<int, vector<spill*>*>(i, t));
	}

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
	XBT_INFO("size is %i",numbytes);
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
	int redId = this->reducerId(reducer);

	vector<spill*>* outRes = new vector<spill*>();
	if (mapOutV->size() > 0) {
		XBT_INFO("the is red id %i", redId);
		for (int a = 0; a < mapOutV->at(redId)->size(); a++) {
			outRes->push_back(mapOutV->at(redId)->at(a));
		}

		reducers.insert(std::pair<int, string>(redId, reducer));

		Message* outResMsg = new Message(msg_type::map_output_res, self,
				reducer, 0, outRes);

		Mailbox::by_name(reducer)->put(outResMsg, 1522);

	}
}
void AppMaster::mapFinished(Message * m) {

	this->numFinishedMappers++;
	requestReducers();
	map<int, vector<spill*>*>* res =
			static_cast<map<int, vector<spill*>*>*>(m->payload);
//	XBT_INFO(printMapOut(mapOutV).c_str());
	for (int i = 0; i < job->numberOfReducers; i++) {
		//XBT_INFO("map out v size before %i  %i", mapOutV->at(i)->size(), i);
		for (int j = 0; j < res->at(i)->size(); j++) {
			mapOutV->at(i)->push_back(res->at(i)->at(j)); //here we push the partitions for each reducer

			numbytes+=res->at(0)->at(j)->ch->size;
		}

		if (this->numFinishedMappers == job->numberOfMappers) {
			spill *lastOne = new spill();
			lastOne->isLast = true;
			lastOne->taskName=m->sender;
			mapOutV->at(i)->push_back(lastOne);

		}
	//	XBT_INFO("map out v size after %i  %i", mapOutV->at(i)->size(), i);
	}

	//free map container
	string s = m->sender.substr(0, m->sender.find('_'));

	string* mm = new string;
	*mm = s;
	freeContainer(mm);

	//send output to all available reducers
	for (int i = 0; i < reducers.size(); i++) {
		if (this->numFinishedMappers == job->numberOfMappers) {
			spill *lastOne = new spill();
			lastOne->isLast = true;
			lastOne->taskName=m->sender;
			res->at(i)->push_back(lastOne);

		}
		Message* outResMsg = new Message(msg_type::map_output_res, self,
				reducers.at(i), 0, res->at(i));
		Mailbox::by_name(reducers.at(i))->put(outResMsg, 1522);

	}
//XBT_INFO(printMapOut(mapOutV).c_str());
}

bool AppMaster::reduceFinished(Message *m) {
	bool isFinished = false;
	this->numFinishedReducers++;
	//free reducer container
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
		XBT_INFO("after send free con reducer");
		Message * finishMsg2 = new Message(msg_type::app_master_finish, self,
				nodeManager, 0, nullptr);
		nodeManagerMb->put(finishMsg2, 1522);
		XBT_INFO("after send free con reducer after node manager");

		Message * finishMsg3 = new Message(msg_type::finish_job, self, rManager,
				0, job);
		rManagerMb->put(finishMsg3, 1522);

		XBT_INFO("after send reduce finish");

		isFinished = true;
	}
	return isFinished;
}

int AppMaster::reducerId(string reducer) {
	auto pos = reducer.find_last_of('_');
	string reducerId = reducer.substr(pos + 1);
	return std::stoi(reducerId);

}

string AppMaster::printSpill(spill* sp) {
	string s = "";
	if(!sp->isLast){
	s += "spill size is " + to_string(sp->ch->size);
	s += "num rec  is " + to_string(sp->records);
	s += "is last  one  " + to_string(sp->isLast);
	}
	else
		s+="this finish spill ";
	return s;
}

string AppMaster::printMapOut(map<int, vector<spill*>*>*a) {

	string s = "this is the output of job  \n";

for(int i=0;i<a->size();i++){

	s+="the spilles of reducer number "+to_string(i)+"\n";

	for(int j=0;j<a->at(i)->size();j++){

		s+=printSpill(a->at(i)->at(j))+"\n";

	}
}

	s+="\n";
	return s;
}
