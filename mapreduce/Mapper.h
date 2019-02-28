/*
 * Mapper.h
 *
 *  Created on: Feb 23, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_MAPPER_H_
#define MAPREDUCE_MAPPER_H_
#include "simgrid/s4u.hpp"
#include "../messages/Message.h"
#include "JobInfo.h"
#include "../distributions/RandClass.h"
using namespace simgrid::s4u;
class Mapper {
public:
int64_t mid;
	allocateRes* res;
	vector<int64_t> spilles;
	string appMasterName;
	string nameNodeName;
	string thisName;
	string dataNodeName;
	JobInfo *job;
	MailboxPtr nnmb, thismb, appMasterMb,dataNodeMb;
	explicit Mapper(string thisName, string appMas, string NameNode,string dataNodeName,
			allocateRes * res);

	void operator()();
	void init();
	virtual ~Mapper();
private:
	static int64_t mapIds;
};

#endif /* MAPREDUCE_MAPPER_H_ */
