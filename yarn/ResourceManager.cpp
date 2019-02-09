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

	thismb = simgrid::s4u::Mailbox::by_name(
			simgrid::s4u::this_actor::get_host()->get_name() + "_"
					+ simgrid::s4u::this_actor::get_name());
	thismb->set_receiver(Actor::self());

}

void ResourceManager::operator()() {

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
		containers.insert(std::pair<string,int>(host->get_name(),numCon));

	}//until here we have map of hosts and how many container they have

}

}

ResourceManager::~ResourceManager() {
// TODO Auto-generated destructor stub
}

