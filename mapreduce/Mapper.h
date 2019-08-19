/*
 * Mapper.h
 *
 *  Created on: Feb 23, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_MAPPER_H_
#define MAPREDUCE_MAPPER_H_
#include "simgrid/s4u.hpp"

//#include "../messages/Message.h"
#include "JobInfo.h"
#include "../distributions/RandClass.h"
#include "../yarn/HddMediator.h"
#include "Combiner.h"
using namespace simgrid::s4u;
class Mapper {
public:
int64_t mid;
Combiner* merger;
	allocateRes* res;
bool minFilesToCombine=false;//false the number of spilles is less than the minimum
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
	map<int, vector<spill*>*>*    writeSpilles(double taskSize,int64_t spillSize);
	//int64_t combine(int64_t recNum);

	spill* exeAndWrPart(int64_t partsize1);
	spill* exePart(int64_t partsize1);
	string printSpill(spill* sp);
	string printMapOut(map<int,vector<spill*>*>*a);
	double copress(double s);
	virtual ~Mapper();
private:
	static int64_t mapIds;
};

#endif /* MAPREDUCE_MAPPER_H_ */
