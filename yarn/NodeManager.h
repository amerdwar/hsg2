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
class NodeManager {
public:
	string rMangerName;
	string nameNodeName;
	string thisName;
	MailboxPtr nnmb;
	MailboxPtr thismb;
	MailboxPtr rManager; //resource manager mailbox

	explicit NodeManager(std::vector<std::string> args);
	void operator()();
	virtual ~NodeManager();
};

#endif /* YARN_NODEMANAGER_H_ */