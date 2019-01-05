/*
 * DadaNode.h
 *
 *  Created on: Dec 29, 2018
 *      Author: alpha
 */

#ifndef HDFS_DATANODE_H_
#define HDFS_DATANODE_H_
#include "NameNode.h"
class DataNode {
public:
	MailboxPtr mailbox;
    map<int64_t,Chunk*> chunks;

	explicit DataNode(std::vector<std::string> args);
	virtual ~DataNode();
	void operator()();
};

#endif /* HDFS_DATANODE_H_ */
