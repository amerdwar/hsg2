/*
 * HddMediator.h
 *
 *  Created on: Feb 25, 2019
 *      Author: alpha
 */

#ifndef YARN_HDDMEDIATOR_H_
#define YARN_HDDMEDIATOR_H_
#include "simgrid/s4u.hpp"
#include "DirFiles.h"
#include "HdfsFile.h"
#include  "NameNode.h"
#include "../messages/Message.h"
using namespace simgrid::s4u;
class HddMediator {
public:
	string dataNodeName;
	string task,sender;
	MailboxPtr dataNode,thismb;
	HddMediator(string dataNodeName,string sender,string task);
	Chunk*  writeCh(int64_t size);
	void readCh(Chunk* ch);
	void deleteCh(Chunk*ch);

	virtual ~HddMediator();
};

#endif /* YARN_HDDMEDIATOR_H_ */
