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
	this->dataNode = simgrid::s4u::this_actor::get_host()->get_name()
			+ "_dataNode";
	this->dataNodemb = Mailbox::by_name(this->dataNode);
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
		case msg_type::map_finish: {
			auto it = std::find(mappers.begin(), mappers.end(), m->sender);
			XBT_INFO("size before erase reducer %s %i", m->sender.c_str(),
					mappers.size());
			mappers.erase(it);
			XBT_INFO("size after erase reducer %s %i", m->sender.c_str(),
					mappers.size());
		}

		}

	} while (m->type != msg_type::end_of_simulation);

}
NodeManager::~NodeManager() {
	// TODO Auto-generated destructor stub
}

void NodeManager::doAllocate(Message* m) {

	allocateRes * res = static_cast<allocateRes*>(m->payload);
	XBT_INFO("in do allocate  %i", res->type);
	switch (res->type) {
	case allocate_type::app_master_all: {
		allocateAppMaster(res);
		break;
	}
	case allocate_type::map_all: {
		allocateMapper(res);
		break;
	}
	case allocate_type::reduce_all: {
		XBT_INFO("in switch reduce");
		allocateReducer1(res);
		break;
	}
	}
}
void NodeManager::allocateAppMaster(allocateRes* res) {
	XBT_INFO("in do app master job name is %s", res->job->jobName.c_str());
	string appm = this_actor::get_host()->get_name() + "_AppMaster";
	// AppMaster(JobInfo* j,string parent,string self,string namenode,string rManager);
	XBT_INFO("the name of app master is %s", appm.c_str());
	ActorPtr appMaster = Actor::create(appm, this_actor::get_host(),
			AppMaster(res->job, thisName, appm, nameNodeName, rMangerName));
	XBT_INFO("created app mas");
	apps.push_back(appm);
}

void NodeManager::allocateMapper(allocateRes* res) {
	//the map name is hostname_nodemanager_m_jobid_fileindex_chunkIndex
	string mapName = res->nodeManager + "_m_" + to_string(res->job->jid) + "_"
			+ to_string(res->fIndex) + "_" + to_string(res->chIndex);
	ActorPtr beater = Actor::create(mapName, this_actor::get_host(),
			Mapper(mapName, res->requester, nameNodeName, dataNode, res));
	XBT_INFO("allocate   map %s", mapName.c_str());
	mappers.push_back(mapName);
}

void NodeManager::allocateReducer1(allocateRes* res) {
//TODO create reduser
	XBT_INFO("allocate reduceeeeeeeeeeeeeeeeee");
}
