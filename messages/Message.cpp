/*
 * Message.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#include "Message.h"

Message::Message(msg_type type,string s,string r,int returnTag,void* payload){
	// TODO Auto-generated constructor stub
this->type=type;
this->payload=payload;
this->sender=s;
this->receiver=r;
this->returnTag=returnTag;


}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

