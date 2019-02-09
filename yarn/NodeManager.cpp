/*
 * NodeManager.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: alpha
 */

#include "NodeManager.h"

NodeManager::NodeManager(std::vector<std::string> args) {

	xbt_assert(args.size() > 0, "the arguments must be more than one");
	this->nameNodeName = args[1];
	this->rMangerName = args[2];
	rManager = Mailbox::by_name(rMangerName);

	nnmb = simgrid::s4u::Mailbox::by_name(nameNodeName);

	thismb = simgrid::s4u::Mailbox::by_name(
			simgrid::s4u::this_actor::get_host()->get_name() + "_"
					+ simgrid::s4u::this_actor::get_name());
	thismb->set_receiver(Actor::self());

}

void NodeManager::operator ()() {

}
NodeManager::~NodeManager() {
	// TODO Auto-generated destructor stub
}

