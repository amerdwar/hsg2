/*
 * Hdd.h
 *
 *  Created on: Jan 19, 2019
 *      Author: alpha
 */

#ifndef HDFS_HDD_H_
#define HDFS_HDD_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "simgrid/s4u.hpp"
#include "../distributions/RandClass.h"
#include "../messages/Message.h"
#include "../messages/HddMsg.h"
using namespace std;
using namespace simgrid::s4u;


class Hdd {
public:
	Mailbox* mailbox;
	double readSpeed=0;
	double writeSpeed=0;
	static double readAccess;
static	double writeAccess;
static double hddSlice;
static double hddCpuUseage;
	double readAccessSize=0;
	double writeAccessSize=0;
int64_t numcompleteWrite=0,numWrite=0;
	//string cachName;
	string storageName="";
	//double cachSpeed;
	double delta=100512;
	bool isIdle=true;
    std::queue<Message*> jobs;
    explicit Hdd(std::string argv);
	explicit Hdd(std::vector<std::string > args);
	double decTimesAndGet(double size);
	virtual ~Hdd();
	void operator()();
};

#endif /* HDFS_HDD_H_ */
