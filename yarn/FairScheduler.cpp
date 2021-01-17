/*
 * YarnScheduler.cpp
 *
 *  Created on: Feb 9, 2019
 *      Author: alpha
 */

#include "FairScheduler.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(FairScheduler,
		"Messages specific for this example");

FairScheduler::FairScheduler(int numAllCon, std::map<string, int> con) {
	// TODO Auto-generated constructor stub
	this->numAllCon = numAllCon;

	this->numContainers = numAllCon; //this is for statistics only
	this->freeContainers = numAllCon; //this is for statistics only

	this->containers = con;
	this->fairIndex = 0;
}
void FairScheduler::addReq(allocateReq *allr) {
	//////XBT_INFO("add req");
	//all req is vector so we push back and serve first then erase first
	if (allr->type == allocate_type::reduce_all
			&& YarnSchedulerBase::type == sch_type::fifo) {
		allReduceReq.push_back(allr);
	} else {
		allReq.push_back(allr);
	}
}
std::vector<allocateRes*> FairScheduler::allocate() {
	/*	switch (this->type) {
	 case sch_type::fifo: {
	 return this->fifo();
	 break;
	 }
	 case sch_type::fair: {
	 return this->fair();
	 break;
	 }
	 case sch_type::capacity: {
	 return this->capacity();
	 break;
	 }
	 default: {
	 return this->fifo();
	 break;
	 }

	 }
	 */

	std::vector<allocateRes*> resV;
	fairIndex = -1;
	while (allReq.size() > 0 && numAllCon > 0) { // start serve allocation requests from the first one
		fairIndex++;
		if (fairIndex == allReq.size())
			fairIndex = 0;
		switch (allReq.at(fairIndex)->type) {
		case allocate_type::map_all: {
			allocateRes *tem = fairServeMap();
			resV.push_back(tem);

			break;
		}
		case allocate_type::reduce_all: {

			allocateRes *tem = fairServeReduce();

			resV.push_back(tem);

			break;
		}
		case allocate_type::app_master_all: {
			allocateRes *tem = fairServeAppMaster();

			resV.push_back(tem);

			break;
		}
		}

	} //end
	this->updateStat();
	this->freeContainers=numAllCon;

	addWaitingJobs();

	end: return resV;

}
void FairScheduler::freeCon(string host) {
	//////XBT_INFO("free container %s", host.c_str());
	containers.at(host)++;
	this->numAllCon++;
	this->updateStat();
	this->freeContainers++;

	//////XBT_INFO("free container %s", host.c_str());
}

void FairScheduler::addJob(JobInfo *job) {

	if (this->startTime==0){

		this->startTime=Engine::get_clock();
		XBT_INFO("in add job %s",to_string(this->startTime).c_str());

	}
	job->addToQtime = Engine::get_clock();
	this->updateStat();
	this->numInQ++;
	this->numDelayedJobs++;
	waitingJobs.push_back(job);

}
FairScheduler::~FairScheduler() {
// TODO Auto-generated destructor stub
}

allocateRes* FairScheduler::getContForCh(Chunk *ch, int index) {
	allocateRes *re = new allocateRes();

//num of nodes that the chunk on them
	int numNode = ch->nodes->size();
	bool isLocality = false;
	for (int n = 0; n < numNode; n++) {
		Mailbox *dataNode = ch->nodes->at(n);
		string dnName = dataNode->get_name();
//then we will get host name from datanode name  hostname_datanode
		string hostName = dnName.substr(0, dnName.find("_"));
		if (containers.at(hostName) > 0) {
			containers.at(hostName) -= 1;
			this->numAllCon--;
			//add allocatte res

			re->chIndex = allReq.at(index)->chIndex;
			re->fIndex = allReq.at(index)->fIndex;
			re->dir = allReq.at(index)->dir;
			re->nodeManager = hostName + "_nodeManager";
			re->requester = allReq.at(index)->requester;
			re->type = allReq.at(index)->type;
			re->job = allReq.at(index)->job;
			isLocality = true;
			break;
		}
	}
	if (!isLocality) {
//TODO select random container if exist and send response

		re->chIndex = allReq.at(index)->chIndex;
		re->fIndex = allReq.at(index)->fIndex;
		re->dir = allReq.at(index)->dir;
		re->nodeManager = getRandCon();
		re->requester = allReq.at(index)->requester;
		re->type = allReq.at(index)->type;
		re->job = allReq.at(index)->job;
	}
	if (re->job->allocateTime==0){

		re->job->allocateTime=Engine::get_clock();//to calculate delay time for the job
	this->totalDelays+=re->job->allocateTime-re->job->addToQtime;
	}
	return re;

}
string FairScheduler::getRandCon() {
	string ra = "";
	//iterate over all containers to get free con
	for (auto tem : containers) {
		//////XBT_INFO("inf for con");
		if (tem.second > 0) {

			containers.at(tem.first) -= 1;
			this->numAllCon--;
			ra = tem.first + "_nodeManager";

			break;
		}
	}
	//////XBT_INFO("in if %s", ra.c_str());
	if (ra.compare("") == 0) {

		////XBT_INFO("exit empty container");
		exit(0);
	}
	return ra;
}

void FairScheduler::printRes(allocateRes *res) {

	////XBT_INFO(" fi=%i ch=%i ty=%i requester=%s", res->fIndex, res->chIndex,
	//res->type, res->requester.c_str());
}
void FairScheduler::printReq(allocateReq *res) {

	////XBT_INFO(" fi=%i ch=%i ty=%i requester=%s", res->fIndex, res->chIndex,
	//res->type, res->requester.c_str());
}

void FairScheduler::addWaitingJobs() {
	while (waitingJobs.size() > 0) {

		//waiting jobs to running and schedule app master container
		allocateReq *jobReq = new allocateReq();
		jobReq->type = allocate_type::app_master_all;
		jobReq->dir = waitingJobs.at(0)->dir;
		jobReq->job = waitingJobs.at(0);
		jobReq->requester = waitingJobs.at(0)->user;

		allReq.push_back(jobReq);
		runningJobs.push_back(waitingJobs.at(0));
		waitingJobs.erase(waitingJobs.begin());
	}
}

allocateRes* FairScheduler::fairServeMap() {

	int fnum = allReq.at(fairIndex)->dir->Files->size();
	int fi = allReq.at(fairIndex)->fIndex;
	int fchNum =
			allReq.at(fairIndex)->dir->Files->at(std::to_string(fi))->chunks->size();
	int c = allReq.at(fairIndex)->chIndex;
	Chunk *ch =
			allReq.at(fairIndex)->dir->Files->at(std::to_string(fi))->chunks->at(
					c);
	allocateRes *re = getContForCh(ch, fairIndex);

	allReq.at(fairIndex)->chIndex++;

	int chSize =
			allReq.at(fairIndex)->dir->Files->at(std::to_string(fi))->chunks->size();
	if (allReq.at(fairIndex)->chIndex == chSize) {
		allReq.at(fairIndex)->chIndex = 0;
		allReq.at(fairIndex)->fIndex++;
		int fSize = allReq.at(fairIndex)->dir->Files->size();
		if (allReq.at(fairIndex)->fIndex == fSize) { //if we serve all files  req
			allReq.erase(allReq.begin() + fairIndex); //sign the req to deque
			fairIndex--;
		}
	}

	return re;

}
allocateRes* FairScheduler::fairServeReduce() {

	allocateRes *re = new allocateRes();
	int reducersNum = allReq.at(0)->reducersNum;
	if (reducersNum > 0) {
		re->chIndex = allReq.at(fairIndex)->chIndex;
		re->fIndex = allReq.at(fairIndex)->fIndex;
		re->dir = allReq.at(fairIndex)->dir;
		re->nodeManager = getRandCon();
		re->requester = allReq.at(fairIndex)->requester;
		//	////XBT_INFO("type is %i", allReq.at(fairIndex)->type);
		re->type = allReq.at(fairIndex)->type;
		re->job = allReq.at(fairIndex)->job;
		re->reducerId = allReq.at(fairIndex)->redId++;
		allReq.at(fairIndex)->reducersNum -= 1;
	}
	if (allReq.at(fairIndex)->reducersNum == 0) {
		allReq.erase(allReq.begin() + fairIndex);
		fairIndex--;
	}

	return re;

}
allocateRes* FairScheduler::fairServeAppMaster() {

	//////XBT_INFO("in fair app master");

	allocateRes *re = new allocateRes();
	re->dir = allReq.at(fairIndex)->dir;
	re->nodeManager = getRandCon();
	re->requester = allReq.at(fairIndex)->requester;
	re->type = allReq.at(fairIndex)->type;
	re->job = allReq.at(fairIndex)->job;

	re->job->allocateTime = Engine::get_clock(); //to calculate delay time for the job
	this->totalDelays += re->job->allocateTime - re->job->addToQtime;

	//delete the req after serve it

	allReq.erase(allReq.begin() + fairIndex);
	fairIndex--;
	return re;

}
void FairScheduler::finishJob(JobInfo *job) {
	this->updateStat();
	this->numInQ -= 1;

}
