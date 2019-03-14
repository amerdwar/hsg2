/*
 * Mapper.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: alpha
 */

#include "Mapper.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Mapper, "Messages specific for this example");
Mapper::Mapper(string thisName, string appMas, string nameNode, string DataNode,
		allocateRes * res) {
	this->mid = mapIds++;
	this->dataNodeName = DataNode;
	this->thisName = thisName;
	this->appMasterName = appMas;
	this->nameNodeName = nameNode;
	this->res = res;
	nodeManagerName = res->nodeManager;
	nodeManagerMb = Mailbox::by_name(nodeManagerName);
	this->job = res->job;
	nnmb = Mailbox::by_name(nameNodeName);
	hddm = new HddMediator(dataNodeName, thisName, thisName);
	dataNodeMb = Mailbox::by_name(dataNodeName);
	appMasterMb = Mailbox::by_name(appMasterName);
	thismb = Mailbox::by_name(thisName);
	XBT_INFO("create map task");

}

void Mapper::operator ()() {
	thismb->set_receiver(Actor::self());
	if (res->type == allocate_type::reduce_all) {
		XBT_INFO("error allocate type error %i   ,%s", res->type,
				this_actor::get_name().c_str());
		exit(1);
	}

	string inputDN = selectInputDataNode();
	HddMediator* inputHDDM = new HddMediator(inputDN, thisName, thisName);
	Chunk* ch = res->dir->Files->at(to_string(res->fIndex))->chunks->at(
			res->chIndex);
	inputHDDM->readCh(ch);


//TODO execute map and write data to hdd
//TODO add while loop and receive heart beats and execute in steps
//the final message contains hdfs file as payload which is ath map output
	Chunk* c1 = hddm->writeCh(100 * 1024 * 1024);
	Chunk* c2 = hddm->writeCh(100 * 1024 * 1024);
	Chunk* c3 = hddm->writeCh(100 * 1024 * 1024);
	Chunk* c4 = hddm->writeCh(100 * 1024 * 1024);

	spilles->push_back(c1);
	spilles->push_back(c2);
	spilles->push_back(c3);
	spilles->push_back(c4);

	hddm->readCh(c1);

	hddm->readCh(c1);
	HdfsFile * hd = new HdfsFile(thisName, thisName, 0); //the file is for encapsulate the output
	hd->chunks = spilles;
	Message* finishMsg = new Message(msg_type::map_finish, thisName,
			appMasterName, 0, hd);

	XBT_INFO("before send finish");
	appMasterMb->put(finishMsg, 1522);
	Message * finishMsg2 = new Message(msg_type::map_finish, thisName,
			nodeManagerName, 0, nullptr);
	nodeManagerMb->put(finishMsg2, 1522);
	XBT_INFO("after send finish");

}
Mapper::~Mapper() {
	// TODO Auto-generated destructor stub
}
int64_t Mapper::mapIds = 0;

void Mapper::init() {

}
string Mapper::selectInputDataNode() {
	Chunk* ch = res->dir->Files->at(to_string(res->fIndex))->chunks->at(
			res->chIndex);
	string inputdataNode = "";
	int numNode = ch->nodes->size();
	bool isLocality = false;
	for (int n = 0; n < numNode; n++) { //check if the chunk node is this datanode
		MailboxPtr dataNode = ch->nodes->at(n);
		string dnName = dataNode->get_name();
		if (this->dataNodeName.compare(dnName) == 0) {
			isLocality = true;
			inputdataNode = dataNodeName;
			break;
		}
	}
	if (!isLocality) { //find data node in the same rack
		string thisRack = this_actor::get_host()->get_property("rack");
		Engine* e = simgrid::s4u::Engine::get_instance();

		auto hosts = e->get_all_hosts();
		for (int n = 0; n < numNode; n++) {
			MailboxPtr dataNode = ch->nodes->at(n);
			string dnName = dataNode->get_name();
			string hostn = dnName.substr(0, dnName.find("_"));
			auto host = e->host_by_name(hostn);
			if (thisRack.compare(host->get_property("rack")) == 0) {
				inputdataNode = dnName;
				isLocality = true;
				break;
			}

		}
		if (!isLocality) { //return rand datanode
			int nodeIndex = RandClass::getRand(0, numNode - 1);
			inputdataNode = ch->nodes->at(nodeIndex)->get_name();
		}

		return inputdataNode;

	}

}
