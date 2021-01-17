/*
 * YarnSchedulerBase.h
 *
 *  Created on: Dec 12, 2020
 *      Author: amer
 */

#ifndef YARN_YARNSCHEDULERBASE_H_
#define YARN_YARNSCHEDULERBASE_H_
#include "../hdfs/NameNode.h"
#include "../mapreduce/JobInfo.h"
#include <fstream>
enum sch_type{
		fifo=0,
		fair,
		capacity
};
class YarnSchedulerBase {
public:

string qName="default";
	  int numContainers=0;
	  int NUM_CUSTOMERS_SERVED=0.0;
	  int MIN_SERVICE_TIME=2.0;
	  int MAX_SERVICE_TIME=3.0;
	  int NUM_LIMITE=20000;

	  int i=0;
	  double startTime=0.0;
	  double endTime=0.0;
	  //define variable of statistics
	  int numDelayedJobs=0.0;

	  double numInQ=0.0;
	  double totalDelays=0.0;
	  double avgDelays=0;
	  double serverUtil=0;
	  double averageQlen=0;
	  double delay=0.6;
	  double timeLastEvent=0.0;
	  double areaNumInQ = 0.0;
	  double areaServerStatus=0.0;
	 double freeContainers=0;

string testStr="";
	YarnSchedulerBase();
	static sch_type type;
	virtual	void addJob(JobInfo* job)=0;
	virtual	void finishJob(JobInfo* job)=0;
	virtual void addReq(allocateReq* allr)=0;
	virtual std::vector<allocateRes*> allocate()=0;
	virtual void freeCon(string host)=0;
	virtual void printRes(allocateRes*)=0;
	virtual void printReq(allocateReq*)=0;
	void updateStat();
	void exportStat();
	virtual ~YarnSchedulerBase();
};

#endif /* YARN_YARNSCHEDULERBASE_H_ */
