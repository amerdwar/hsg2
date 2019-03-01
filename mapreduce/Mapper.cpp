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
	this->job = res->job;
	nnmb = Mailbox::by_name(nameNodeName);
	hddm=new HddMediator(dataNodeName,thisName,thisName);
	dataNodeMb = Mailbox::by_name(dataNodeName);
	appMasterMb = Mailbox::by_name(appMasterName);
	thismb = Mailbox::by_name(thisName);
	XBT_INFO("create map task");
}

void Mapper::operator ()() {
	thismb->set_receiver(Actor::self());
	if (res->type == allocate_type::reduce_all) {
		XBT_INFO("error allocate type error %i   ,%s",res->type,this_actor::get_name().c_str());
		exit(1);
	}

//TODO execute map and write data to hdd
//TODO add while loop and receive heart beats and execute in steps
//the final message contains hdfs file as payload which is ath map output
	Chunk* c1=hddm->writeCh(100*1024*1024);
	Chunk* c2=hddm->writeCh(100*1024*1024);
	Chunk* c3=hddm->writeCh(100*1024*1024);
	Chunk* c4=hddm->writeCh(100*1024*1024);

	spilles->push_back(c1);
	spilles->push_back(c2);
	spilles->push_back(c3);
	spilles->push_back(c4);

hddm->readCh(c1);

hddm->readCh(c1);
		HdfsFile * hd = new HdfsFile(thisName,thisName, 0);//the file is for encapsulate the output

	Message* finishMsg = new Message(msg_type::map_finish, thisName,
			appMasterName, 0, hd);

	XBT_INFO("before send finish");
	appMasterMb->put(finishMsg, 1522);
	//TODO send finish message to datanode to free container
	XBT_INFO("after send finish");

}
Mapper::~Mapper() {
	// TODO Auto-generated destructor stub
}
int64_t Mapper::mapIds = 0;

void Mapper::init() {

}
