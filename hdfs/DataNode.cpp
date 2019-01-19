/*
 * DadaNode.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: alpha
 */

#include "DataNode.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(dataNode, "Messages specific for this example");

DataNode::DataNode(std::vector<std::string> args) {
	// TODO Auto-generated constructor stub
	storage_list = new std::vector<string>();
	//sList =simgrid::s4u::Host::current()->get_mounted_storages();

	for (auto const& a : sList) {
		XBT_INFO(" mount is %s attach is %s ", a.first.c_str(),
				a.second->get_name().c_str());
		storage_list->push_back(a.second->get_name());

	}
	mailbox = Mailbox::by_name(
			this_actor::get_host()->get_name() + "_" + this_actor::get_name());
	mailbox->set_receiver(Actor::self());
}
void DataNode::operator()() {

	Message * m = nullptr;
	msg_type ty = msg_type::any;
	simgrid::s4u::CommPtr comm_rec = nullptr;
	simgrid::s4u::CommPtr comm_send = nullptr;
	do {
		void *t;

		m = static_cast<Message*>(mailbox->get());

//m=static_cast<Message*> (mailbox->get());

		switch (m->type) {
		case msg_type::end_of_simulation: {

			break;
		}
		case msg_type::cl_dn_wr_ch: {
			Chunk * ch = static_cast<Chunk*>(m->payload);

			ch->storage = getRandStorage();

			chunks.insert(std::pair<int64_t, Chunk*>(ch->chId, ch));

			ch->writeIndex += 1;
//1048576 size take 1 ms to write ,some thing lime access time
double a =Engine::get_clock();
			auto aa=Storage::by_name(ch->storage)->write_async(ch->size*2);
			//Storage::by_name(ch->storage)->write(ch->size);
			if (ch->writeIndex < ch->nodes->size()) {
				m->payload = ch;
				m->sender = m->receiver;
				m->receiver = ch->nodes->at(ch->writeIndex)->get_name();
				ch->nodes->at(ch->writeIndex)->put(m, ch->size);
				aa->wait();
				double b =Engine::get_clock();
				XBT_INFO("the time is %f ",b-a);
			} else { //this is the last node in the pipline
				aa->wait();
				ch->writeIndex -= 1; //the index of the last node
				ch->writeIndex -= 1; //the index of the  previous node
				m->payload = ch;
				m->type = msg_type::dn_ack_wr_ch;
				m->sender = m->receiver;
				if (ch->writeIndex >= 0) {
					m->receiver = ch->nodes->at(ch->writeIndex)->get_name();
					ch->nodes->at(ch->writeIndex)->put(m, 1522);
				} else { //send the ack to client

					m->receiver = ch->clinetMB->get_name();
					ch->clinetMB->put(m, 1522);
				}

			}

			break;
		}
		case msg_type::cl_dn_re_ch: {
			Chunk * ch = static_cast<Chunk*>(m->payload);
			string tem = m->sender;
			m->sender = m->receiver;
			m->receiver = tem;
			Storage::by_name(chunks.at(ch->chId)->storage)->read(ch->size);
			Mailbox::by_name(m->receiver)->put(m, ch->size);
			break;
		}
		case msg_type::dn_ack_wr_ch: {
			Chunk * ch = static_cast<Chunk*>(m->payload);
			ch->writeIndex -= 1; //the index of the  previous node
			m->payload = ch;
			//m->type=msg_type::dn_ack_wr_ch;
			m->sender = m->receiver;
			if (ch->writeIndex >= 0) {
				m->receiver = ch->nodes->at(ch->writeIndex)->get_name();
				ch->nodes->at(ch->writeIndex)->put(m, 1522);
			} else { //send the ack to client

				m->receiver = ch->clinetMB->get_name();
				ch->clinetMB->put(m, 1522);
			}

		}
		}

	} while (ty != msg_type::end_of_simulation);

}
DataNode::~DataNode() {
	// TODO Auto-generated destructor stub
}
string DataNode::getRandStorage() {
	return storage_list->at(RandClass::getRand(0, storage_list->size() - 1));

}

