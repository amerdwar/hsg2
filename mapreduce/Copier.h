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
#include "AsyncWriter.h"
using namespace simgrid::s4u;
class Copier {
public:
	vector<ActorPtr> actorPtrV;
	int64_t ackNum=0,reqNum=0;
	int64_t asyncWrId=0;
	Combiner* merger;
	int64_t numBytes=0;
	queue<vector<spill*>*>* q;
	int nCopiers, nFreeCopiers;
	string thisName, parent,dataNode;
	MailboxPtr thismb, parentMb,thismbForDataNode;
	JobInfo* job;
	HddMediator *hddmed;
	int64_t memBytes,bufferMemBytes;
	vector<spill*>* outDiskV,*outMemV;
	map<string,int> readVAck;
    std::vector<simgrid::s4u::ExecPtr> pending_comms;
	explicit Copier(string thisName, string parent, int nCopiers, JobInfo *job,string dataNode);
	void sendReadReg(vector<spill*> *v );//send read request and start exec on this chunk to merge
	spill* exe(vector<spill*>*v);
	vector<vector<spill*>*> *  getMapsVecors(vector<spill*>* v);
	void spillAndCompine(spill* sp) ;
	void AsyncDirectSpill(spill* sp);
	string printMap(map<string,int> rm);
	void toDisk();

	void directSpill(spill* sp);
	void operator()();

	virtual ~Copier();
};

#endif /* MAPREDUCE_COPIER_H_ */
