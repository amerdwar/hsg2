/*
 * HeartBeater.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: alpha
 */

#include "HeartBeater.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(HearBeater, "Messages specific for this example");
HeartBeater::HeartBeater(string args) {
	parentName=args;
 parentMb= simgrid::s4u::Mailbox::by_name(parentName);
		thismb = simgrid::s4u::Mailbox::by_name(
				simgrid::s4u::this_actor::get_host()->get_name() + "_"
						+ simgrid::s4u::this_actor::get_name());
		thismb->set_receiver(Actor::self());


}

void HeartBeater::operator ()(){
	Message *ms=new Message(msg_type::heart_beat,thismb->get_name(),thismb->get_name(),0,nullptr);
	thismb->put(ms,0);
	do{
//sleep and send heart beat to parent
		ms = static_cast<Message*>(thismb->get());
		switch (ms->type) {
				case msg_type::end_of_simulation: {
					XBT_INFO("hdd end simulation ");
					break;
				}
				case msg_type::heart_beat:{
							Message *ms=new Message(msg_type::heart_beat,thismb->get_name(),parentName,0,nullptr);
							parentMb->put(ms,0);
							thismb->put(ms,0);
							this_actor::sleep_for(1);
					break;
				}

		}

	}while (ms->type!=msg_type::end_of_simulation);
}

HeartBeater::~HeartBeater() {
	// TODO Auto-generated destructor stub
}

