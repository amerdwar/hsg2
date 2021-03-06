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
#include <fstream>
#include <boost/format.hpp>
class Client {

public:
string nameNode ;
simgrid::s4u::Mailbox* nnmb,*thismb;
string f1,f2;
	explicit Client(std::vector<std::string> args);
	explicit Client(string arg);
	void write();
	void read();
	virtual ~Client();
	void operator()();
};

#endif /* HDFS_CLIENT_H_ */
