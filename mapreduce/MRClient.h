/*
 * MRClient.h
 *  MRClient send job to resource manager
 *  Created on: Feb 4, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_MRCLIENT_H_
#define MAPREDUCE_MRCLIENT_H_
#include "JobInfo.h"
#include "simgrid/s4u.hpp"
#include "../hdfs/HdfsClient.h"
#include "../hdfs/HdfsFile.h"
#include "../distributions/RandClass.h"
#include "../messages/Message.h"
#include "../yarn/HddMediator.h"



using namespace simgrid::s4u;
class MRClient {
public:
	string rMangerName;
	string nameNodeName;
	string thisName;
	MailboxPtr nnmb;
	MailboxPtr thismb;

	MailboxPtr rManager; //resource manager mailbox
vector<int64_t> jobs;
	explicit MRClient(std::vector<std::string> args);
	explicit MRClient(string arg);
	void initJob(JobInfo* job);
	void sendJob(JobInfo* j);
	void writeDate(JobInfo* j);
	void operator()();
	~MRClient();

};
#endif /* MAPREDUCE_MRCLIENT_H_ */
