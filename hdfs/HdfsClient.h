/*
 * HdfsClient.h
 *
 *  Created on: Jan 9, 2019
 *      Author: alpha
 */

#ifndef HDFS_HDFSCLIENT_H_
#define HDFS_HDFSCLIENT_H_
#include "simgrid/s4u.hpp"
#include "DirFiles.h"
#include "HdfsFile.h"
#include  "NameNode.h"
#include "../messages/Message.h"
using namespace simgrid::s4u;
class HdfsClient {
public:

	simgrid::s4u::Mailbox* nnmb;
	simgrid::s4u::Mailbox* thismb;
	string nameNode;
	HdfsClient(simgrid::s4u::Mailbox* nnmb,simgrid::s4u::Mailbox* thismb);
	bool writeFile(HdfsFile *h);
	bool read(HdfsFile* hr);
	virtual ~HdfsClient();
};

#endif /* HDFS_HDFSCLIENT_H_ */
