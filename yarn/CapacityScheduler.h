/*
 * CapacityScheduler.h
 *
 *  Created on: Feb 9, 2019
 *      Author: alpha
 */

#ifndef YARN_CAPACITYSCHEDULER_H_
#define YARN_CAPACITYSCHEDULER_H_
#include "../hdfs/NameNode.h"
#include "../mapreduce/JobInfo.h"
#include "YarnSchedulerBase.h"
#include "Capacity.h"
#include "../resources/JsonPlatform.h"
#include <map>

class CapacityScheduler : public YarnSchedulerBase{
public:

	int numAllCon;

	vector<Capacity*>* queus;
	map <string,FIFOScheduler*> allQ;
	map<string, std::vector<allocateReq*> > allReq;






	void printRes(allocateRes* res) ;
	void printReq(allocateReq* res) ;

	CapacityScheduler(int numAllCon,	std::map<string,int> containers);
	void addJob(JobInfo* job);
	void addReq(allocateReq* allr);
	std::vector<allocateRes*> allocate();

	void finishJob(JobInfo *job);
	void exportQstat();


void insertFromMapToMap(std::map<string,int> containers
,string jobName,int startIndex,int count);


	void freeCon(string host);
	virtual ~CapacityScheduler();
};

#endif /* YARN_CAPACITYSCHEDULER_H_ */
