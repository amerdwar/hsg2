/*
 * Mapper.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: alpha
 */

#include "Mapper.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Mapper, "Messages specific for this example");
Mapper::Mapper(string thisName, string appMas, string nameNode,
		allocateRes * res) {
	this->thisName = thisName;
	this->appMasterName = appMas;
	this->nameNodeName = nameNode;
	this->res = res;
	this->job = res->job;
	nnmb = Mailbox::by_name(nameNodeName);
	appMasterMb = Mailbox::by_name(appMasterName);
	thismb = Mailbox::by_name(thisName);
	XBT_INFO("create map task");
}

void Mapper::operator ()() {
	thismb->set_receiver(Actor::self());
	if (res->type != allocate_type::map_all) {
		XBT_INFO("error allocate type error");
		exit(1);
	}

//TODO execute map and write data to hdd
//TODO add while loop and receive heart beats and execute in steps

}
Mapper::~Mapper() {
	// TODO Auto-generated destructor stub
}

void Mapper::init() {
	for (auto const& a : sList) {

		string actorName = this_actor::get_host()->get_name() + "_"
				+ a.second->get_name(); //the name of the hdd actor is hostname_hddname
		storage_list->push_back(actorName);
	}

}
string Mapper::getRandStorage() {
	return storage_list->at(RandClass::getRand(0, storage_list->size() - 1));

}
void Mapper::WriteToHdd(int64_t si) {
	string storage = getRandStorage();
	Chunk *ch = new Chunk("default", "def", 0, si);
	Message *m = new Message(msg_type::hdd, thisName, storage,
			hdd_Access::hdd_write, ch);
	m->generator = m->sender;
	Mailbox::by_name(storage)->put(m, 0);
 acksMap.insert(std::pair<int64_t, int >(m->genId, 1));


}

void Mapper::readFromHdd(int64_t si) {
	string storage = getRandStorage();
	Chunk *ch = new Chunk("default", "def", 0, si);
	Message *m = new Message(msg_type::hdd, thisName, storage,
			hdd_Access::hdd_read, ch);
	m->generator = m->sender;
	Mailbox::by_name(storage)->put(m, 0);
	acksMap.insert(std::pair<int64_t, int >(m->genId, 1));
}
