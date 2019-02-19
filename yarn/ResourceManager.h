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
#include "YarnScheduler.h"

class ResourceManager {
public:
	string nameNodeName;
	string heartBeater;
	MailboxPtr nnmb;
	MailboxPtr thismb;
	int numCorePerContainer = 1; //to specify the containers number on each host
	int numAllContainers = 0;
	int numFreeContainers = 0;
	std::map<string, int> containers;
	std::vector<JobInfo*> waitingJobs;
	std::vector<JobInfo*> finishedJobs;
	std::vector<JobInfo*> runningJobs;
	YarnScheduler* scheduler;
	explicit ResourceManager(std::vector<std::string> args);
	ResourceManager();
	void operator()();
	void initNodeManagers();
	virtual ~ResourceManager();
};

#endif /* YARN_RESOURCEMANAGER_H_ */
