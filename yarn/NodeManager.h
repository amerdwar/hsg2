/*
 * NodeManager.h
 *
 *  Created on: Feb 6, 2019
 *      Author: alpha
 */

#ifndef YARN_NODEMANAGER_H_
#define YARN_NODEMANAGER_H_
#include "simgrid/s4u.hpp"
#include "../hdfs/NameNode.h"
#include "../mapreduce/JobInfo.h"
#include "HeartBeater.h"
#include "../mapreduce/AppMaster.h"
#include "../mapreduce/Mapper.h"
#include "../mapreduce/Reducer.h"

class NodeManager {
public:

	string  dataNode;
	string rMangerName;
	string nameNodeName;
	string thisName;
	MailboxPtr nnmb, dataNodemb;
	vector<string> apps;
	vector<string> mappers;
	vector<string> reducers;
	MailboxPtr thismb;
	MailboxPtr rManager; //resource manager mailbox

	explicit NodeManager(std::vector<std::string> args);
	void operator()();
	void doAllocate(Message *m);
	void allocateAppMaster(allocateRes* res);
	void allocateMapper(allocateRes* res);
	void allocateReducer1(allocateRes* res);

	virtual ~NodeManager();
};

#endif /* YARN_NODEMANAGER_H_ */
