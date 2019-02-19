/*
 * ResourceManager.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: alpha
 */

#include "ResourceManager.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(ResourceManager,
		"Messages specific for this example");
ResourceManager::ResourceManager(std::vector<std::string> args) {
	xbt_assert(args.size() > 0, "the arguments must be more than one");
	this->nameNodeName = args[1];

	nnmb = simgrid::s4u::Mailbox::by_name(nameNodeName);
	thismb = Mailbox::by_name(
			this_actor::get_host()->get_name() + "_" + this_actor::get_name());
	thismb->set_receiver(Actor::self());
	initNodeManagers();
	numFreeContainers = numAllContainers; //on create all the containers are free
	scheduler=new YarnScheduler(numAllContainers,containers);

//run heart beater
	heartBeater = this_actor::get_host()->get_name() + "_heartBeater";
	Actor::create(heartBeater, this_actor::get_host(), thismb->get_name());

}

void ResourceManager::operator()() {

	Message* m = nullptr;
	do {
		//sleep and send heart beat to parent
		m = static_cast<Message*>(thismb->get());
		switch (m->type) {
		case msg_type::end_of_simulation: {
			XBT_INFO("resource manager end of simulation end simulation ");
			//send this message to heart beater
			Mailbox::by_name(heartBeater)->put(m, 0);
			//TODO send this message to all node managers
			break;
		}
		case msg_type::cl_rm_send_job: {
			JobInfo * j = static_cast<JobInfo*>(m->payload);
			scheduler->waitingJobs.push_back(j);
//TODO make allocation requests

			break;
		}

		case msg_type::heart_beat: {
			//TODO update stat and jobs
			std::vector<allocateRes>resV =scheduler->allocate();
			for(auto resp:resV){
//TODO send resp to requester
			}
			//take job
			break;
		}
		case msg_type::free_con:{
//TODO free con by call scheduler.freeCon
			break;
		}
		case msg_type::finish_job:{
			//TODO print result of job

		}

		}

	} while (m->type != msg_type::end_of_simulation);

}

void ResourceManager::initNodeManagers() {

	Engine* e = simgrid::s4u::Engine::get_instance();

	auto racks =
			e->get_filtered_netzones<simgrid::kernel::routing::ClusterZone>();
	for (auto rack : racks) {
		for (auto host : rack->get_all_hosts()) {
			host->set_property("rack", rack->get_name());
			XBT_INFO("pro  %s", host->get_property("rack"));
			int numCon = host->get_core_count() / this->numCorePerContainer; //num containers = num cores per host/num core per container
			numAllContainers += numCon;
			containers.insert(std::pair<string, int>(host->get_name(), numCon));
		} //until here we have map of hosts and how many container they have

	}

}

ResourceManager::~ResourceManager() {
// TODO Auto-generated destructor stub
}

