/*
 * Message.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#include "Message.h"

Message::Message(msg_type type, string s, string r, int returnTag,
		void* payload) {
	// TODO Auto-generated constructor stub
	this->ack_num=0;
	this->type = type;
	this->payload = payload;
	this->sender = s;
	this->receiver = r;
	this->returnTag = returnTag;
	this->id = ++allMid; //the message id
	double d = simgrid::s4u::Engine::get_clock();
	auto a = boost::format(
			"time %5%  create Message (t=%1% ,s=%2% ,r=%3% , id=%4%) \n") % type
			% sender % receiver % id % d;
	traceStr = traceStr + a.str();
this->genId=this->id;
this->cop_num=0;
}

void Message::trace(string s) {
	double d = simgrid::s4u::Engine::get_clock();
	auto a = boost::format("time %1% m= %2% \n") % s % d;
	traceStr = traceStr + a.str();
}
int64_t Message::allMid = 0;

Message::~Message() {
	// TODO Auto-generated destructor stub
}
string Message::toString(){
	string str="";
	str+="message ("+std::to_string(this->type);

	str+=" , "+std::to_string(this->id);
	str+=" , "+this->sender;
	str+=" , "+this->receiver;
	str+=" , "+std::to_string(this->returnTag);
	str+=" , "+this->generator;
	str+=" , "+std::to_string(this->genId);

	str+=" )";


	return str;
}

Message* Message::copy() {
	Message* ms = new Message(this->type, this->sender, this->receiver,
			this->returnTag, this->payload);
	ms->genId = this->genId;
	ms->generator = this->generator;
ms->cop_num=this->cop_num;
ms->ack_num=this->ack_num;
ms->mapperName=this->mapperName;

	return ms;
}
