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
#include <queue>
using namespace simgrid::s4u;
class Copier {
public:
	queue<Message*>* q;
	int nCopiers, nFreeCopiers;
	string thisName, parent;
	MailboxPtr thismb, parentMb;
	JobInfo* job;
	explicit Copier(string thisName, string parent, int nCopiers, JobInfo *job);
	void sendReadReg(Message *m);
	void operator()();
	virtual ~Copier();
};

#endif /* MAPREDUCE_COPIER_H_ */
