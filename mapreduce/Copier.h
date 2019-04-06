/*
 * Copier.h
 *
 *  Created on: Mar 30, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_COPIER_H_
#define MAPREDUCE_COPIER_H_
#include "simgrid/s4u.hpp"
#include "../messages/Message.h"
#include "JobInfo.h"
#include "Combiner.h"
#include <queue>
using namespace simgrid::s4u;
class Copier {
public:
	Combiner* merger;
	queue<vector<spill*>*>* q;
	int nCopiers, nFreeCopiers;
	string thisName, parent,dataNode;
	MailboxPtr thismb, parentMb;
	JobInfo* job;
	HddMediator *hddmed;
	int64_t memBytes;
	vector<spill*>* outDiskV,*outMemV;
	map<string,int> readVAck;
    std::vector<simgrid::s4u::ExecPtr> pending_comms;
	explicit Copier(string thisName, string parent, int nCopiers, JobInfo *job,string dataNode);
	void sendReadReg(vector<spill*> *v );//send read request and start exec on this chunk to merge
	spill* exe(vector<spill*>*v);
	vector<vector<spill*>*> *  getMapsVecors(vector<spill*>* v);
	void spillAndCompine(spill* sp) ;

	void toDisk();
	void operator()();

	virtual ~Copier();
};

#endif /* MAPREDUCE_COPIER_H_ */
