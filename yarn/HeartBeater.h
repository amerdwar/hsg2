/*
 * HeartBeater.h
 *
 *  Created on: Feb 7, 2019
 *      Author: alpha
 */

#ifndef YARN_HEARTBEATER_H_
#define YARN_HEARTBEATER_H_
#include "../hdfs/NameNode.h"
#include "simgrid/s4u.hpp"
#include "../messages/Message.h"
class HeartBeater {
public:
	string parentName ;
	simgrid::s4u::Mailbox* parentMb,*thismb;
	explicit HeartBeater(string args,string hb);
	void operator()();
	virtual ~HeartBeater();
};

#endif /* YARN_HEARTBEATER_H_ */
