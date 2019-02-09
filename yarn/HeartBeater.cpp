/*
 * HeartBeater.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: alpha
 */

#include "HeartBeater.h"

HeartBeater::HeartBeater(string args) {
	parentName=args;
 parentMb= simgrid::s4u::Mailbox::by_name(parentName);
		thismb = simgrid::s4u::Mailbox::by_name(
				simgrid::s4u::this_actor::get_host()->get_name() + "_"
						+ simgrid::s4u::this_actor::get_name());
		thismb->set_receiver(Actor::self());


}

void HeartBeater::operator ()(){
	while (true){
//sleep and send heart beat to parent
		this_actor::sleep_for(1000);
		Message *ms=new Message(msg_type::heart_beat,thismb->get_name(),parentName,0,nullptr);
		parentMb->put(ms,0);
	}
}

HeartBeater::~HeartBeater() {
	// TODO Auto-generated destructor stub
}

