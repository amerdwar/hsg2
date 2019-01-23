/*
 * HddMsg.h
 *
 *  Created on: Jan 20, 2019
 *      Author: alpha
 */

#ifndef MESSAGES_HDDMSG_H_
#define MESSAGES_HDDMSG_H_
#include "../hdfs/NameNode.h"
class HddMsg {
public:
	double totalTime;
	double times=0;
double deltaTime;
	HddMsg(double totalTime,double deltaTime);
	bool hasNext();
	double decTimesAndGet();

	virtual ~HddMsg();
};

#endif /* MESSAGES_HDDMSG_H_ */
