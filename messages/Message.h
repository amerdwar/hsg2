/*
 * Message.h
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#ifndef MESSAGES_MESSAGE_H_
#define MESSAGES_MESSAGE_H_
#include <string>
#include <boost/format.hpp>
#include <simgrid/s4u.hpp>
#include "../commons/Types.h"
using namespace std;

class Message {
public:
	string traceStr="";

	msg_type type;
	string sender;
	string receiver;
	string generator;
string mapperName="";//this for mapper only
	int returnTag;
	void* payload;
	int64_t id;
	int64_t genId=0;
int cop_num;
int ack_num;
	Message(msg_type,string,string,int,void*);
	Message* copy();
	virtual ~Message();
	void trace(string s);
	string toString();
private:
	static int64_t allMid;
};


#endif /* MESSAGES_MESSAGE_H_ */

