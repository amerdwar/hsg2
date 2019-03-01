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
	sch_type type = sch_type::fifo;
	int numAllCon;
	std::vector<allocateReq*> allReq;
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
	std::vector<allocateRes*>  serveMap();
	std::vector<allocateRes*>  serveReduce();
	std::vector<allocateRes*>  serveAppMaster();
	allocateRes* getContForCh(Chunk* ch);
	void printRes(allocateRes*);
	void printReq(allocateReq*);
	void freeCon(string host);
	virtual ~YarnScheduler();
};

#endif /* YARN_YARNSCHEDULER_H_ */
