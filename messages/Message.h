/*
 * Message.h
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#ifndef MESSAGES_MESSAGE_H_
#define MESSAGES_MESSAGE_H_
#include <string>
#include "../commons/Types.h"
using namespace std;

class Message {
public:
	int type;
	string sender;
	string receiver;
	int returnTag;
	void* payload;

	Message(msg_type,string,string,int,void*);
	virtual ~Message();
};


#endif /* MESSAGES_MESSAGE_H_ */

