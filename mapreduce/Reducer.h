/*
 * Reducer.h
 *
 *  Created on: Mar 1, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_REDUCER_H_
#define MAPREDUCE_REDUCER_H_
#include "simgrid/s4u.hpp"
//#include "../messages/Message.h"
#include "JobInfo.h"
#include "../distributions/RandClass.h"
#include "../yarn/HddMediator.h"
#include "Copier.h"
#include "Combiner.h"
#include "../hdfs/HdfsClient.h"
class Reducer {
public:
	int64_t rid,reqNum=0;
	allocateRes* res;
	vector<Chunk*>* spilles = new vector<Chunk*>();
	string appMasterName, coName;
	string nameNodeName;
	string thisName;
	string dataNodeName, nodeManagerName;
	JobInfo *job;
	MailboxPtr nnmb, thismb, appMasterMb, dataNodeMb, nodeManagerMb;
	HddMediator *hddm;
	vector<spill*>* inputs;
	vector<spill*>* inputsMem;
	HdfsFile* outputf;
	Combiner* merger;

	explicit Reducer(string thisName, string appMas, string NameNode,
			string dataNodeName, allocateRes * res);

	void operator()();
	void copyOutPut();
	string printSpill(spill* sp);
	string printMapOut(vector<spill*>* a);
	HdfsFile* exeReduce();
	bool sendMapToCopier(vector<spill*>* payload);

	virtual ~Reducer();
private:
	static int64_t reduceIds;
};

#endif /* MAPREDUCE_REDUCER_H_ */
