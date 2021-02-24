/*
 * YarnScheduler.cpp
 *
 *  Created on: Feb 9, 2019
 *      Author: alpha
 */

#include "FIFOScheduler.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(fifoScheduler,
		"Messages specific for this example");

FIFOScheduler::FIFOScheduler(int numAllCon, std::map<string, int> con) {
	// TODO Auto-generated constructor stub
	this->numAllCon = numAllCon;
	this->numContainers=numAllCon;//this is for statistics only
	this->freeContainers=numAllCon;//this is for statistics only
	this->containers = con;
	this->fairIndex = 0;
}
void FIFOScheduler::addReq(allocateReq *allr) {

	//all req is vector so we push back and serve first then erase first
	if (allr->type == allocate_type::reduce_all) {

		allReduceReq.push_back(allr);
	} else {

		allReq.push_back(allr);
	}
}
std::vector<allocateRes*> FIFOScheduler::allocate() {
	std::vector<allocateRes*> resV;

	while (allReduceReq.size() > 0 && numAllCon > 0) { // start serve allocation requests from the first one

		std::vector<allocateRes*> tem = fifoServeReduce();
		auto a = this_actor::exec_async(222);


		for (auto item : tem) {
			resV.push_back(item);
		}


	}

	while (allReq.size() > 0 && numAllCon > 0) { // start serve allocation requests from the first one
		switch (allReq.at(0)->type) {

		case allocate_type::app_master_all: {
			std::vector<allocateRes*> tem = fifoServeAppMaster();
			for (auto item : tem) {
				resV.push_back(item);
			}
			break;
		}
		case allocate_type::reduce_all: {
			std::vector<allocateRes*> tem = fifoServeReduce();
			auto a = this_actor::exec_async(222);

			for (auto item : tem) {
				resV.push_back(item);
			}
			break;
		}
		case allocate_type::map_all: {
			std::vector<allocateRes*> tem = fifoServeMap();

			for (auto item : tem) {
				resV.push_back(item);

			}

			break;
		}
		}

	} //end
	this->updateStat();
	this->freeContainers=numAllCon;
	addWaitingJobs();
	end: return resV;

}

void FIFOScheduler::freeCon(string host) {
	//////XBT_INFO("free container %s", host.c_str());
	if (containers.find(host) != containers.end()) {
		containers.at(host)++;
		this->numAllCon++;
		this->updateStat();
		this->freeContainers++;

	}

	//////XBT_INFO("free container %s", host.c_str());
}

void FIFOScheduler::addJob(JobInfo *job) {
	XBT_INFO("add job fifo %s", job->jobName.c_str());
/*	if (this->numDelayedCustomers == 0) {
		this->startTime = Engine::get_clock();

	}

	if (this->freeContainers == 0) {
		this->numInQ += 1;
	} else {
		//there is free container
		delay = 0; //there is no delay because the customer has been served im
		this->totalDelays += delay;

		this->i = this->i + 1;

	}*/
	if (this->startTime==0){

		this->startTime=Engine::get_clock();
		XBT_INFO("in add job %s",to_string(this->startTime).c_str());

	}
	this->updateStat();
	this->numInQ++;
	this->numDelayedJobs++;
	job->addToQtime=Engine::get_clock();
	waitingJobs.push_back(job);

}
FIFOScheduler::~FIFOScheduler() {
// TODO Auto-generated destructor stub
}

allocateRes* FIFOScheduler::getContForCh(Chunk *ch, int index) {
	allocateRes *re = new allocateRes();

//num of nodes that the chunk on them
	int numNode = ch->nodes->size();
	bool isLocality = false;
	for (int n = 0; n < numNode; n++) {
		Mailbox *dataNode = ch->nodes->at(n);
		string dnName = dataNode->get_name();
//then we will get host name from datanode name  hostname_datanode
		string hostName = dnName.substr(0, dnName.find("_"));
		if (containers.find(hostName) != containers.end()) {
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
string FIFOScheduler::getRandCon() {
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
std::vector<allocateRes*> FIFOScheduler::fifoServeMap() {
	std::vector<allocateRes*> resV;

	int fnum = allReq.at(0)->dir->Files->size();
	for (int fi = allReq.at(0)->fIndex; fi < fnum; fi++) {
		int fchNum =
				allReq.at(0)->dir->Files->at(std::to_string(fi))->chunks->size();
		for (int c = allReq.at(0)->chIndex; c < fchNum; c++) {

			Chunk *ch =
					allReq.at(0)->dir->Files->at(std::to_string(fi))->chunks->at(
							c);

			allocateRes *re = getContForCh(ch, 0);

			resV.push_back(re);
			allReq.at(0)->chIndex++;
			if (this->numAllCon == 0) {
				//there is no more free containers so end allocation but go to end
				int chSize =
						allReq.at(0)->dir->Files->at(std::to_string(fi))->chunks->size();
				if (allReq.at(0)->chIndex == chSize) {
					allReq.at(0)->chIndex = 0;
					allReq.at(0)->fIndex++;
					int fSize = allReq.at(0)->dir->Files->size();
					if (allReq.at(0)->fIndex == fSize) //if we serve all files  req
						allReq.erase(allReq.begin()); //sign the req to deque
				}
				goto end;
			}

		} //end for (ch
		allReq.at(0)->chIndex = 0;
		allReq.at(0)->fIndex++;
		int fSize = allReq.at(0)->dir->Files->size();
		if (allReq.at(0)->fIndex == fSize) //if we serve all files  req
			allReq.erase(allReq.begin()); //sign the req to deque

	}

	end: return resV;
}
std::vector<allocateRes*> FIFOScheduler::fifoServeReduce() {
	std::vector<allocateRes*> resV;

	int reducersNum = allReduceReq.at(0)->reducersNum;
	for (int i = 0; i < reducersNum; i++) {
		if (this->numAllCon > 0) {
			allocateRes *re = new allocateRes();
			re->chIndex = allReduceReq.at(0)->chIndex;
			re->fIndex = allReduceReq.at(0)->fIndex;
			re->dir = allReduceReq.at(0)->dir;
			re->nodeManager = getRandCon();
			re->requester = allReduceReq.at(0)->requester;
			//XBT_INFO("type is %i", allReq.at(0)->type);
			re->type = allReduceReq.at(0)->type;
			re->job = allReduceReq.at(0)->job;
			re->reducerId = allReduceReq.at(0)->redId++;

			allReduceReq.at(0)->reducersNum -= 1;

			resV.push_back(re);


		} else {
			break;
		}

	}
	if (allReduceReq.at(0)->reducersNum == 0) {
		allReduceReq.erase(allReduceReq.begin());
	}

	return resV;

}
std::vector<allocateRes*> FIFOScheduler::fifoServeAppMaster() {
	//////XBT_INFO("in app master");
	std::vector<allocateRes*> resV;
	allocateRes *re = new allocateRes();
	re->dir = allReq.at(0)->dir;
	re->nodeManager = getRandCon();
	re->requester = allReq.at(0)->requester;
	re->type = allReq.at(0)->type;
	re->job = allReq.at(0)->job;


	resV.push_back(re);

	//delete the req after serve it
	allReq.erase(allReq.begin());

	return resV;
}

void FIFOScheduler::printRes(allocateRes *res) {

	////XBT_INFO(" fi=%i ch=%i ty=%i requester=%s", res->fIndex, res->chIndex,
	//res->type, res->requester.c_str());
}
void FIFOScheduler::printReq(allocateReq *res) {

	////XBT_INFO(" fi=%i ch=%i ty=%i requester=%s", res->fIndex, res->chIndex,
	//res->type, res->requester.c_str());
}

void FIFOScheduler::addWaitingJobs() {
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
void FIFOScheduler::finishJob(JobInfo* job) {

	this->updateStat();
	this->numInQ --;
}
