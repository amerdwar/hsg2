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
	JobInfo* job;
int numAllMappers=0,numAllReducers=0,numFinishedMappers,numFinishedReducers;
	string parent,self,nameNode,rManager;
	MailboxPtr parentMb,thisMb,nameNodeMb,rManagerMb;
	vector<string> mappers;
	vector<string> reducers;
vector<HdfsFile*> mapOutV ;
	explicit AppMaster(JobInfo* j,string parent,string self,string namenode,string rManager);
	void operator()();
	void sendMapRequest();
	void sendAllocationFromAppMasterToNodeManager(allocateRes *res);
	void requestReducers();
	void sendReduceRequest();
	void sendOutTellNow(string reducer);
	void mapFinished(Message *m);
 void freeContainer(string *con);
	virtual ~AppMaster();
};

#endif /* MAPREDUCE_APPMASTER_H_ */
