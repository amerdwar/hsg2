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
#include "../yarn/HddMediator.h"
using namespace simgrid::s4u;
class Mapper {
public:
int64_t mid;
	allocateRes* res;
	vector<Chunk*>* spilles=new vector<Chunk*>();
	string appMasterName;
	string nameNodeName;
	string thisName;
	string dataNodeName,nodeManagerName;
	JobInfo *job;
	//mapper variables

	//end mapper variables

	MailboxPtr nnmb, thismb, appMasterMb,dataNodeMb,nodeManagerMb;
	HddMediator *hddm;
	explicit Mapper(string thisName, string appMas, string NameNode,string dataNodeName,
			allocateRes * res);

	void operator()();
	void init();
	string selectInputDataNode();
	virtual ~Mapper();
private:
	static int64_t mapIds;
};

#endif /* MAPREDUCE_MAPPER_H_ */
