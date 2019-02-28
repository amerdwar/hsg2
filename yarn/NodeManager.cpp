/*
 * NodeManager.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: alpha
 */

#include "NodeManager.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(nodeManager, "Messages specific for this example");
NodeManager::NodeManager(std::vector<std::string> args) {

	xbt_assert(args.size() > 0, "the arguments must be more than one");
	this->nameNodeName = args[1];
	this->rMangerName = args[2];
	rManager = Mailbox::by_name(rMangerName);

	nnmb = simgrid::s4u::Mailbox::by_name(nameNodeName);
	thisName = simgrid::s4u::this_actor::get_host()->get_name() + "_"
			+ simgrid::s4u::this_actor::get_name();
	thismb = simgrid::s4u::Mailbox::by_name(thisName);
	thismb->set_receiver(Actor::self());

	heartBeater = this_actor::get_host()->get_name() + "_heartBeater";
	ActorPtr beater = Actor::create(heartBeater, this_actor::get_host(),
			HeartBeater(thismb->get_name(), heartBeater));

}

void NodeManager::operator ()() {
	Message* m = nullptr;
	do {
		//sleep and send heart beat to parent

		m = static_cast<Message*>(thismb->get());

		switch (m->type) {
		case msg_type::end_of_simulation: {
			XBT_INFO("resource manager end of simulation end simulation ");
			//send this message to heart beater
			Mailbox::by_name(heartBeater)->put(m, 0);
			//TODO send this message to all containers if exists
			break;
		}
		case msg_type::allocate_res: {
			doAllocate(m);
			break;
		}
		case msg_type::heart_beat: {

			break;
		}

		}

	} while (m->type != msg_type::end_of_simulation);

}
NodeManager::~NodeManager() {
	// TODO Auto-generated destructor stub
}

void NodeManager::doAllocate(Message* m) {
	allocateRes * res = static_cast<allocateRes*>(m->payload);
	switch (res->type) {
	case allocate_type::app_master_all: {
		allocateAppMaster(res);
		break;
	}
	case allocate_type::reduce_all: {

		break;
	}
	case allocate_type::map_all: {

		break;
	}
	}
}
void NodeManager::allocateAppMaster(allocateRes* res) {
	XBT_INFO("in do app master");
	string appm = this_actor::get_host()->get_name() + "_AppMaster";
	// AppMaster(JobInfo* j,string parent,string self,string namenode,string rManager);
	ActorPtr appMaster = Actor::create(appm, this_actor::get_host(),
			AppMaster(res->job, thisName, appm, nameNodeName, rMangerName));
	apps.push_back(appm);

}
