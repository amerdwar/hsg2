/*
 * Mapper.h
 *
 *  Created on: Feb 23, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_MAPPER_H_
#define MAPREDUCE_MAPPER_H_
#include "simgrid/s4u.hpp"
#include "../messages/Message.h"
#include "JobInfo.h"
#include "../distributions/RandClass.h"
using namespace simgrid::s4u;
class Mapper {
public:
	std::unordered_map<std::string, simgrid::s4u::Storage*> const& sList =
			simgrid::s4u::Host::current()->get_mounted_storages();
	std::vector<string> *storage_list=new 	std::vector<string>();
	allocateRes* res;
	string appMasterName;
	string nameNodeName;
	string thisName;
	JobInfo *job;
	MailboxPtr nnmb, thismb, appMasterMb;
	explicit Mapper(string thisName, string appMas, string NameNode,
			allocateRes * res);
	string getRandStorage();
	void operator()();
	void init();

	virtual ~Mapper();
};

#endif /* MAPREDUCE_MAPPER_H_ */
