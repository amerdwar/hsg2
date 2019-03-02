/*
 * YarnScheduler.cpp
 *
 *  Created on: Feb 9, 2019
 *      Author: alpha
 */

#include "YarnScheduler.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(yarnsch, "Messages specific for this example");
YarnScheduler::YarnScheduler(int numAllCon, std::map<string, int> con) {
	// TODO Auto-generated constructor stub
	this->numAllCon = numAllCon;
	this->containers = con;


}
void YarnScheduler::addReq(allocateReq* allr) {
XBT_INFO("add req");
	allReq.push_back(allr); //all req is vector so we push back and serve first then erase first

}
std::vector<allocateRes*> YarnScheduler::allocate() {
	switch (this->type) {
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

}
void YarnScheduler::freeCon(string host) {
	XBT_INFO("free container %s",host.c_str());
	containers.at(host)++;
	this->numAllCon++;
	XBT_INFO("free container %s",host.c_str());
}
std::vector<allocateRes*> YarnScheduler::fifo() {
	std::vector<allocateRes*> resV;

	while (allReq.size() > 0 && numAllCon > 0) { // start serve allocation requests from the first one
		switch (allReq.at(0)->type) {
		case allocate_type::map_all: {
			std::vector<allocateRes*> tem = serveMap();
			for (auto item : tem) {
				resV.push_back(item);

			}
			break;
		}
		case allocate_type::reduce_all: {
XBT_INFO("reduce in scheeeerwerwerwerwerwerwer");
			std::vector<allocateRes*> tem = serveReduce();
			for (auto item : tem) {
				resV.push_back(item);
			}
			break;
		}
		case allocate_type::app_master_all: {
			std::vector<allocateRes*> tem = serveAppMaster();
			for (auto item : tem) {
				resV.push_back(item);
			}
			break;
		}
		}

	} //end

	while (waitingJobs.size() > 0) {

//waiting jobs to running and schedule app master container
		allocateReq* jobReq=new allocateReq();
		jobReq->type = allocate_type::app_master_all;
		jobReq->dir = waitingJobs.at(0)->dir;
		jobReq->job = waitingJobs.at(0);
		jobReq->requester = waitingJobs.at(0)->user;

		allReq.push_back(jobReq);
		runningJobs.push_back(waitingJobs.at(0));
		waitingJobs.erase(waitingJobs.begin());
	}

	end: return resV;

}
std::vector<allocateRes*> YarnScheduler::fair() {
	std::vector<allocateRes*> a;

	return a;
}
std::vector<allocateRes*> YarnScheduler::capacity() {
	std::vector<allocateRes*> a;

	return a;
}
void YarnScheduler::addJob(JobInfo* job) {
	waitingJobs.push_back(job);

}
YarnScheduler::~YarnScheduler() {
// TODO Auto-generated destructor stub
}

allocateRes* YarnScheduler::getContForCh(Chunk* ch) {
	allocateRes* re=new allocateRes();

//num of nodes that the chunk on them
	int numNode = ch->nodes->size();
	bool isLocality = false;
	for (int n = 0; n < numNode; n++) {
		MailboxPtr dataNode = ch->nodes->at(n);
		string dnName = dataNode->get_name();
//then we will get host name from datanode name  hostname_datanode
		string hostName = dnName.substr(0, dnName.find("_"));
		if (containers.at(hostName) > 0) {
			containers.at(hostName) -= 1;
			this->numAllCon--;
			//add allocatte res

			re->chIndex = allReq.at(0)->chIndex;
			re->fIndex = allReq.at(0)->fIndex;
			re->dir = allReq.at(0)->dir;
			re->nodeManager = hostName + "_nodeManager";
			re->requester = allReq.at(0)->requester;
			re->type = allReq.at(0)->type;
			re->job=allReq.at(0)->job;
			isLocality = true;
			break;
		}
	}
	if (!isLocality) {
//TODO select random container if exist and send response

		re->chIndex = allReq.at(0)->chIndex;
		re->fIndex = allReq.at(0)->fIndex;
		re->dir = allReq.at(0)->dir;
		re->nodeManager = getRandCon();
		re->requester = allReq.at(0)->requester;
		re->type = allReq.at(0)->type;
		re->job=allReq.at(0)->job;
	}

	return re;

}
string YarnScheduler::getRandCon() {
	string ra;
	//iterate over all containers to get free con
	for (auto tem : containers) {
		XBT_INFO("inf for con");
		if (tem.second > 0) {

			containers.at(tem.first) -= 1;
			this->numAllCon--;
			ra = tem.first+"_nodeManager";

			break;
		}
	}
	//XBT_INFO("in if %s", ra.c_str());
	return ra;
}
std::vector<allocateRes*> YarnScheduler::serveMap() {
	std::vector<allocateRes*> resV;

	int fnum = allReq.at(0)->dir->Files->size();
	for (int fi = allReq.at(0)->fIndex; fi < fnum; fi++) {
		int fchNum =
				allReq.at(0)->dir->Files->at(std::to_string(fi))->chunks->size();
		for (int c = allReq.at(0)->chIndex; c < fchNum; c++) {
			Chunk* ch =
					allReq.at(0)->dir->Files->at(std::to_string(fi))->chunks->at(
							c);
			allocateRes* re = getContForCh(ch);

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
std::vector<allocateRes*> YarnScheduler::serveReduce() {
	std::vector<allocateRes*> resV;
	allocateRes* re=new allocateRes();
	int reducersNum = allReq.at(0)->reducersNum;
	for (int i = 0; i < reducersNum; i++) {
		if (this->numAllCon > 0) {
			re->chIndex = allReq.at(0)->chIndex;
			re->fIndex = allReq.at(0)->fIndex;
			re->dir = allReq.at(0)->dir;
			re->nodeManager = getRandCon();
			re->requester = allReq.at(0)->requester;
			XBT_INFO("type is %i",allReq.at(0)->type);
			re->type = allReq.at(0)->type;
			re->job=allReq.at(0)->job;
			allReq.at(0)->reducersNum -= 1;
			resV.push_back(re);
		} else {
			break;
		}

	}
	if (allReq.at(0)->reducersNum == 0) {
		allReq.erase(allReq.begin());
	}

	return resV;

}
std::vector<allocateRes*> YarnScheduler::serveAppMaster() {
	XBT_INFO("in app master");
	std::vector<allocateRes*> resV;
	allocateRes* re=new allocateRes();
	re->dir = allReq.at(0)->dir;
	re->nodeManager = getRandCon();
	re->requester = allReq.at(0)->requester;
	re->type = allReq.at(0)->type;
re->job=allReq.at(0)->job;
	resV.push_back(re);

	//delete the req after serve it
	allReq.erase(allReq.begin());

	return resV;
}

void YarnScheduler::printRes(allocateRes* res){

XBT_INFO(" fi=%i ch=%i ty=%i requester=%s",res->fIndex,res->chIndex,res->type,res->requester.c_str());
}
void YarnScheduler::printReq(allocateReq* res){

XBT_INFO(" fi=%i ch=%i ty=%i requester=%s",res->fIndex,res->chIndex,res->type,res->requester.c_str());
}
