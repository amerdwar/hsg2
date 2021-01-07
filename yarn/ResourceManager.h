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
#include "YarnSchedulerBase.h"
#include "FIFOScheduler.h"
#include "FairScheduler.h"
#include "CapacityScheduler.h"
#include "HeartBeater.h"

class ResourceManager {
public:
	int endCounter=0;
	string nameNodeName,thisName;
	string heartBeater;
	Mailbox* nnmb;
	Mailbox* thismb;
	static int numCorePerContainer ; //to specify the containers number on each host
	int numAllContainers = 0;
	int numFreeContainers = 0;
	std::map<string, int> containers;
	std::vector<JobInfo*> waitingJobs;
	std::vector<JobInfo*> finishedJobs;
	std::vector<JobInfo*> runningJobs;
	YarnSchedulerBase * getScheduler(int numAllContainers , std::map<string, int> containers);
	YarnSchedulerBase* scheduler;
	explicit ResourceManager(std::vector<std::string> args);
	ResourceManager();
	void operator()();
	void initNodeManagers();

	virtual ~ResourceManager();
};

#endif /* YARN_RESOURCEMANAGER_H_ */
