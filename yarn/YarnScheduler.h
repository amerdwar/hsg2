/*
 * YarnScheduler.h
 *
 *  Created on: Feb 9, 2019
 *      Author: alpha
 */

#ifndef YARN_YARNSCHEDULER_H_
#define YARN_YARNSCHEDULER_H_
#include "../hdfs/NameNode.h"
#include "../mapreduce/JobInfo.h"

enum sch_type{
		fifo=0,
		fair,
		capacity
};
class YarnScheduler {
public:
	static sch_type type;
	int numAllCon;
	int fairIndex;
	std::vector<allocateReq*> allReq;
	std::vector<allocateReq*> allReduceReq;
	std::vector<allocateRes*> allRes;

	std::vector<JobInfo *> waitingJobs;
	std::vector<JobInfo *> runningJobs;
	std::vector<JobInfo *> finishedJobs;

	std::map<string,int> containers;
	YarnScheduler(int numAllCon,	std::map<string,int> containers);
	void addJob(JobInfo* job);
	void addReq(allocateReq* allr);
	std::vector<allocateRes*> allocate();
	std::vector<allocateRes*> fifo();
	std::vector<allocateRes*> fair();
	std::vector<allocateRes*> capacity();

	string getRandCon();
	void addWaitingJobs();
	std::vector<allocateRes*>  fifoServeMap();
	std::vector<allocateRes*>  fifoServeReduce();
	std::vector<allocateRes*>  fifoServeAppMaster();

	allocateRes* fairServeMap();
	allocateRes*  fairServeReduce();
	allocateRes*  fairServeAppMaster();

	allocateRes* getContForCh(Chunk* ch,int index);
	void printRes(allocateRes*);
	void printReq(allocateReq*);
	void freeCon(string host);
	virtual ~YarnScheduler();
};

#endif /* YARN_YARNSCHEDULER_H_ */
