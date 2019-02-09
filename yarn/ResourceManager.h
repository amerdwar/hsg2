/*
 * ResourceManager.h
 *
 *  Created on: Feb 6, 2019
 *      Author: alpha
 */

#ifndef YARN_RESOURCEMANAGER_H_
#define YARN_RESOURCEMANAGER_H_
#include "simgrid/s4u.hpp"
#include "../hdfs/NameNode.h"
#include "../mapreduce/JobInfo.h"

class ResourceManager {
public:
	string nameNodeName;
	MailboxPtr nnmb;
	MailboxPtr thismb;
	int numCorePerContainer = 1;//to specify the containers number on each host
	std::map<string,int>containers;
	std::vector<JobInfo> waitingJobs;
	std::vector<JobInfo> finishedJobs;
	std::vector<JobInfo> runningJobs;

	explicit ResourceManager(std::vector<std::string> args);
	ResourceManager();
	void operator()();
	void initNodeManagers();
	virtual ~ResourceManager();
};

#endif /* YARN_RESOURCEMANAGER_H_ */
