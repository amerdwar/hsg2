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
	this->mid=mapIds++;
	this->dataNodeName=DataNode;
	this->thisName = thisName;
	this->appMasterName = appMas;
	this->nameNodeName = nameNode;
	this->res = res;
	this->job = res->job;
	nnmb = Mailbox::by_name(nameNodeName);
	dataNodeMb = Mailbox::by_name(dataNodeName);
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
int64_t Mapper::mapIds=0;

void Mapper::init() {


}
