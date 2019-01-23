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
Message* Message::copy() {
	Message* ms = new Message(this->type, this->sender, this->receiver,
			this->returnTag, this->payload);
	ms->genId = this->genId;
	ms->generator = this->generator;
	return ms;
}
