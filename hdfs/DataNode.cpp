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
		//xbt_info(" mount is %s attach is %s ", a.first.c_str(),
			//	a.second->get_name().c_str());

		string actorName = this_actor::get_host()->get_name() + "_"
				+ a.second->get_name(); //the name of the hdd actor is hostname_hddname
				//here we create hdd actor

		Actor::create(actorName, this_actor::get_host(),
				Hdd(a.second->get_name()));

		//here we push the mailboxes of the hdd actors
		storage_list->push_back(actorName);
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
			//xbt_info(" the storage is %s", ch->storage.c_str());

			chunks.insert(std::pair<int64_t, Chunk*>(ch->chId, ch));
			//xbt_info(" write index before %i ", ch->writeIndex);
			ch->writeIndex += 1;
			//xbt_info(" write index after %i ", ch->writeIndex);
			//send message to hdd actor to write the message
			m->type = msg_type::hdd;
			m->sender = mailbox->get_name();
			m->receiver = ch->storage;
			m->returnTag = hdd_Access::hdd_write;
			m->payload = ch;
			m->genId = m->id;


			Chunk* chForSend=ch->copy();
			Mailbox::by_name(ch->storage)->put(m, 0);
			//xbt_info(" send messaage to hdd %s", ch->storage.c_str());

			Message* ms = m->copy();

			hddPendings.insert(std::pair<int64_t, Message *>(m->genId, m));

			if (chForSend->writeIndex < chForSend->nodes->size()) {
				ms->type = msg_type::cl_dn_wr_ch;
				ms->payload = chForSend;
				ms->sender = mailbox->get_name();;
				ms->receiver = chForSend->nodes->at(chForSend->writeIndex)->get_name();

				ddPendings.insert(std::pair<int64_t, Message *>(ms->genId, ms));//add message to wait for ach
				//xbt_info(
				//		"send message to other and sizze pending is %i  next is %s",
					//	ddPendings.size(),
						//ch->nodes->at(ch->writeIndex)->get_name().c_str());
				chForSend->nodes->at(chForSend->writeIndex)->put(ms, chForSend->size);

			} else { //this is the last node in the pipline

				//send ack message to this_actor
				//xbt_info(" after send ack ");
				chForSend->writeIndex -= 1; //the index of the last node

				ms->payload = chForSend;
				ms->type = msg_type::dn_ack_wr_ch;
				ms->receiver = ms->sender = mailbox->get_name();

				mailbox->put(ms, 0);
				ddPendings.insert(std::pair<int64_t, Message *>(ms->genId, ms)); //add message to wait for ach
				//xbt_info("send message to self and sizze pending is %i",
					//	ddPendings.size());
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
			//recieve ack
			auto ms = m;
			ddPendings.erase(m->genId);
			m = ms;
			auto it = hddPendings.find(m->genId);
			//xbt_info(" receivd ack form node %i ", it == hddPendings.end());
			if (it == hddPendings.end()) { //receive ack from hdd so send the ack to the previous node
				//xbt_info(" yes it is  10");

				Chunk * ch = static_cast<Chunk*>(m->payload);
				//xbt_info(" yes it is  11");
				ch->writeIndex -= 1; //the index of the  previous node
				m->payload = ch;
				//m->type=msg_type::dn_ack_wr_ch;
				m->sender = mailbox->get_name();
				//xbt_info(" yes it is");
				if (ch->writeIndex >= 0) {
					//xbt_info(" yes it is 1");
					m->receiver = ch->nodes->at(ch->writeIndex)->get_name();
					//xbt_info(" yes it is 2");
					ch->nodes->at(ch->writeIndex)->put(m, 1522);
					//xbt_info(" yes it is 3");
				} else { //send the ack to client
					//xbt_info(" yes it is 4");
					m->receiver = ch->clinetMB->get_name();
					//xbt_info(" yes it is 5");
					ch->clinetMB->put(m, 1522);
					//xbt_info(" yes it is 6");
				}

			}
			break;
		}

		case msg_type::hdd_ack: {
			//recieve ack
			//xbt_info("recevie akk from hdd");
			auto ms = m;
			hddPendings.erase(m->genId);
			m = ms;
			//xbt_info("after erase");
			auto it = ddPendings.find(m->genId);
			//xbt_info(" the find res %i %s %s", it == ddPendings.end(),
				//	m->sender.c_str(), m->receiver.c_str());
			if (it == ddPendings.end()) { //receive ack from hdd so send the ack to the previous node

				Chunk * ch = static_cast<Chunk*>(m->payload);
				ch->writeIndex -= 1; //the index of the  previous node
				m->payload = ch;
				m->type = msg_type::dn_ack_wr_ch;
				m->sender = m->receiver;

				if (ch->writeIndex >= 0) {
					//xbt_info("in if nodes %i index %i ", ch->nodes->size(),
							//ch->writeIndex);
					m->receiver = ch->nodes->at(ch->writeIndex)->get_name();
					//xbt_info("in if  2 %i ", m->genId);
					ch->nodes->at(ch->writeIndex)->put(m, 1522);
					//xbt_info("in if  3 %i ", m->genId);
				} else { //send the ack to client
					//xbt_info("in else %i ", m->genId);
					m->receiver = ch->clinetMB->get_name();
					//xbt_info("in else 1%i ", m->genId);
					ch->clinetMB->put(m, 1522);
					//xbt_info("in else 2 %i ", m->genId);
				}

			}
			break;
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

