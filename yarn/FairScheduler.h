/*
 * FairScheduler.h
 *
 *  Created on: Feb 9, 2019
 *      Author: alpha
 */

#ifndef YARN_FAIRSCHEDULER_H_
#define YARN_FAIRSCHEDULER_H_
#include "../hdfs/NameNode.h"
#include "../mapreduce/JobInfo.h"
#include "YarnSchedulerBase.h"

class FairScheduler : public YarnSchedulerBase{
public:

	int numAllCon;
	int fairIndex;
	std::vector<allocateReq*> allReq;
	std::vector<allocateReq*> allReduceReq;
	std::vector<allocateRes*> allRes;

	std::vector<JobInfo *> waitingJobs;
	std::vector<JobInfo *> runningJobs;
	std::vector<JobInfo *> finishedJobs;

	std::map<string,int> containers;
	FairScheduler(int numAllCon,	std::map<string,int> containers);
	void addJob(JobInfo* job);
	void addReq(allocateReq* allr);
	std::vector<allocateRes*> allocate();

	string getRandCon();
	void addWaitingJobs();


	allocateRes* fairServeMap();
	allocateRes*  fairServeReduce();
	allocateRes*  fairServeAppMaster();

	allocateRes* getContForCh(Chunk* ch,int index);
	void printRes(allocateRes*);
	void printReq(allocateReq*);
	void freeCon(string host);
	virtual ~FairScheduler();
};

#endif /* YARN_FAIRSCHEDULER_H_ */
