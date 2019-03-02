/*
 * Reducer.h
 *
 *  Created on: Mar 1, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_REDUCER_H_
#define MAPREDUCE_REDUCER_H_
#include "simgrid/s4u.hpp"
#include "../messages/Message.h"
#include "JobInfo.h"
#include "../distributions/RandClass.h"
#include "../yarn/HddMediator.h"

class Reducer {
public:
	int64_t rid;
	allocateRes* res;
	vector<Chunk*>* spilles = new vector<Chunk*>();
	string appMasterName;
	string nameNodeName;
	string thisName;
	string dataNodeName,nodeManagerName;
	JobInfo *job;
	MailboxPtr nnmb, thismb, appMasterMb, dataNodeMb,nodeManagerMb;
	HddMediator *hddm;
	vector<HdfsFile*> inputs=new vector <HdfsFile*>();
	HdfsFile* outputf;
	explicit Reducer(string thisName, string appMas, string NameNode,string dataNodeName,
			allocateRes * res);

	void operator()();

	Reducer();
	virtual ~Reducer();
private:
	static int64_t reduceIds;
};

#endif /* MAPREDUCE_REDUCER_H_ */
