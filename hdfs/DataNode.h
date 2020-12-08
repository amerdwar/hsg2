/*
 * DadaNode.h
 *
 *  Created on: Dec 29, 2018
 *      Author: alpha
 */

#ifndef HDFS_DATANODE_H_
#define HDFS_DATANODE_H_
#include "NameNode.h"
#include "../distributions/RandClass.h"
#include "Hdd.h"
class DataNode {
public:
	Mailbox* mailbox;
    map<int64_t,Chunk*> chunks;
    map<int64_t, std::map<int,int>> acksMap;

    std::vector<string> *storage_list;
    std::unordered_map<std::string, simgrid::s4u::Storage*> const&
															sList=simgrid::s4u::Host::current()->get_mounted_storages();
	explicit DataNode(std::vector<std::string > args);
	virtual ~DataNode();
	string getRandStorage();
	void operator()();
};

#endif /* HDFS_DATANODE_H_ */
