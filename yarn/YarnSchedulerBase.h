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

enum sch_type{
		fifo=0,
		fair,
		capacity
};
class YarnSchedulerBase {
public:
	YarnSchedulerBase();
	static sch_type type;
	virtual	void addJob(JobInfo* job)=0;
	virtual void addReq(allocateReq* allr)=0;
	virtual std::vector<allocateRes*> allocate()=0;
	virtual void freeCon(string host)=0;
	virtual void printRes(allocateRes*)=0;
	virtual void printReq(allocateReq*)=0;
	virtual ~YarnSchedulerBase();
};

#endif /* YARN_YARNSCHEDULERBASE_H_ */
