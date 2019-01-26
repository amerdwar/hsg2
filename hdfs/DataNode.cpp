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

	do {
		void *t;

		m = static_cast<Message*>(mailbox->get());
		switch (m->type) {
		case msg_type::end_of_simulation: {

			break;
		}
		case msg_type::cl_dn_wr_ch: {
			Chunk * ch = static_cast<Chunk*>(m->payload);

			ch->storage = getRandStorage();				//select storage

			chunks.insert(std::pair<int64_t, Chunk*>(ch->chId, ch));//add to chunks map

			Message* ms = m->copy();				//copy message to send it//

			m->type = msg_type::hdd;
			m->sender = mailbox->get_name();
			m->generator = m->sender;
			m->receiver = ch->storage;
			m->returnTag = hdd_Access::hdd_write;
			m->payload = ch;

			Chunk* chForSend = ch->copy();

			std::map<int, int> cop;
			cop.insert(std::pair<int, int>(ch->writeIndex, 2));
			auto second = acksMap.insert(
					std::pair<int64_t, std::map<int, int> >(m->genId, cop));
			if(second.second==false){

				acksMap.at(m->genId).insert(std::pair<int, int>(ch->writeIndex, 2));
			}

XBT_INFO("insert id %i  ch %i",m->genId,ch->writeIndex);

			Mailbox::by_name(ch->storage)->put(m, 0);

			chForSend->writeIndex += 1;
			if (chForSend->writeIndex < chForSend->nodes->size()) {
				ms->type = msg_type::cl_dn_wr_ch;
				ms->payload = chForSend;
				ms->sender = mailbox->get_name();
				ms->receiver =
						chForSend->nodes->at(chForSend->writeIndex)->get_name();

				//xbt_info(
				//		"send message to other and sizze pending is %i  next is %s",
				//	ddPendings.size(),
				//ch->nodes->at(ch->writeIndex)->get_name().c_str());
				XBT_INFO("ms %s ", ms->toString().c_str());
				chForSend->nodes->at(chForSend->writeIndex)->put(ms,
						chForSend->size);

			} else { //this is the last node in the pipline

				//send ack message to this_actor
				//xbt_info(" after send ack ");
				chForSend->writeIndex -= 1; //the index of the last node
				XBT_INFO("the chunk index is last index %i ",
						chForSend->writeIndex);
				ms->payload = chForSend;
				ms->type = msg_type::dn_ack_wr_ch;
				ms->receiver = ms->sender = mailbox->get_name();

				mailbox->put(ms, 0);
				XBT_INFO("send message ack dd %s ", ms->toString().c_str());
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

			Chunk * ch = static_cast<Chunk*>(m->payload);

			XBT_INFO("here %i   %i size  %i",m->genId,ch->writeIndex,acksMap.at(m->genId).size());
			acksMap.at(m->genId).at(ch->writeIndex) -= 1;
			XBT_INFO("that");


			if (acksMap.at(m->genId).at(ch->writeIndex) == 0) { //receive ack from hdd so send the ack to the previous node
				//xbt_info(" yes it is  10");


				//xbt_info(" yes it is  11");
				ch->writeIndex -= 1; //the index of the  previous node
				XBT_INFO("the chunk index  mmmmis %i ", ch->writeIndex);
				m->payload = ch;
				//m->type=msg_type::dn_ack_wr_ch;
				m->sender = mailbox->get_name();
				//xbt_info(" yes it is");
				if (ch->writeIndex >= 0) {
					//xbt_info(" yes it is 1");
					m->receiver = ch->nodes->at(ch->writeIndex)->get_name();
					//xbt_info(" yes it is 2");
					ch->nodes->at(ch->writeIndex)->put(m, 1522);
					XBT_INFO("send message ack dd %s ", m->toString().c_str());
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

			Chunk * ch = static_cast<Chunk*>(m->payload);
			acksMap.at(m->genId).at(ch->writeIndex) -= 1;


			//	m->sender.c_str(), m->receiver.c_str());
			if (acksMap.at(m->genId).at(ch->writeIndex) == 0) { //receive ack from hdd so send the ack to the previous node


				ch->writeIndex -= 1; //the index of the  previous node
				XBT_INFO("the chunk index is %i ", ch->writeIndex);
				m->payload = ch;
				m->type = msg_type::dn_ack_wr_ch;
				m->sender = m->receiver;

				if (ch->writeIndex >= 0) {
					//xbt_info("in if nodes %i index %i ", ch->nodes->size(),
					//ch->writeIndex);
					m->receiver = ch->nodes->at(ch->writeIndex)->get_name();
					//xbt_info("in if  2 %i ", m->genId);
					ch->nodes->at(ch->writeIndex)->put(m, 1522);
					XBT_INFO("send message ack hdd %s ", m->toString().c_str());
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

