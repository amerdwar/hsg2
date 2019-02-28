/*
 * HeartBeater.cpp
 *
 *  Created on: Feb 7, 2019
 *      Author: alpha
 */

#include "HeartBeater.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(HearBeater, "Messages specific for this example");
HeartBeater::HeartBeater(string args,string hb) {
	parentName = args;

	thismb = simgrid::s4u::Mailbox::by_name(hb);


	parentMb = simgrid::s4u::Mailbox::by_name(parentName);
}

void HeartBeater::operator ()() {
	thismb->set_receiver(Actor::self());
	XBT_INFO(" heart is : %s", thismb->get_name().c_str());

	Message *ms = new Message(msg_type::heart_beat, thismb->get_name(),
			parentMb->get_name(), 0, nullptr);

	thismb->put(ms, 0);
	do {


//sleep and send heart beat to parent
		ms = static_cast<Message*>(thismb->get());
		switch (ms->type) {
		case msg_type::end_of_simulation: {
			XBT_INFO("heart beater end simulation ");
			break;
		}
		case msg_type::heart_beat: {
			Message *ms = new Message(msg_type::heart_beat, thismb->get_name(),
					parentName, 0, nullptr);
			parentMb->put(ms, 0);
			thismb->put(ms, 0);
			this_actor::sleep_for(1);
			break;
		}

		}

	} while (ms->type != msg_type::end_of_simulation);
}

HeartBeater::~HeartBeater() {
	// TODO Auto-generated destructor stub
}

