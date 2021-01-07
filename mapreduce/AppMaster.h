/*
 * AppMaster.h
 *
 *  Created on: Feb 23, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_APPMASTER_H_
#define MAPREDUCE_APPMASTER_H_
#include "simgrid/s4u.hpp"
#include "../messages/Message.h"
#include "JobInfo.h"

using namespace simgrid::s4u;
class AppMaster {
public:
	bool reduceReqIsSent=false;
	static	double slowStartNumFinishedMappers;
	JobInfo* job;
int64_t numbytes=0;
int64_t numOfFinishedMappers=0;
int numAllMappers=0,numAllReducers=0,numFinishedMappers,numFinishedReducers;
	string parent,self,nameNode,rManager,nodeManager;
	Mailbox* parentMb,*thisMb,*nameNodeMb,*rManagerMb,*nodeManagerMb;
	vector<string> mappers;
	map<int,string> reducers;
	map<int,vector<spill*>*>*  mapOutV ;
	explicit AppMaster(JobInfo* j,string parent,string self,string namenode,string rManager);
	void operator()();
	void sendMapRequest();
	void sendAllocationFromAppMasterToNodeManager(allocateRes *res);
	void requestReducers();
	void sendReduceRequest();
	void sendOutTellNow(string reducer);
	void mapFinished(Message *m);
	bool reduceFinished(Message *m);
	int reducerId(string reducer);
 void freeContainer(string *con);
 string printSpill(spill* sp) ;

 string printMapOut(map<int, vector<spill*>*>*a) ;
	virtual ~AppMaster();
};

#endif /* MAPREDUCE_APPMASTER_H_ */
