/*
 * Client.h
 *
 *  Created on: Jan 3, 2019
 *      Author: alpha
 */

#ifndef HDFS_CLIENT_H_
#define HDFS_CLIENT_H_
#include "NameNode.h"
#include "HdfsClient.h"
class Client {

public:
string nameNode ;
simgrid::s4u::MailboxPtr nnmb,thismb;
	explicit Client(std::vector<std::string> args);
	explicit Client(string arg);
	void write();
	void read();
	virtual ~Client();
	void operator()();
};

#endif /* HDFS_CLIENT_H_ */
