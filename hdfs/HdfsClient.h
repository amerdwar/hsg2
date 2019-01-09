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
#include "../messages/Message.h"
using namespace simgrid::s4u;
class HdfsClient {
public:
	simgrid::s4u::MailboxPtr nnmb;
	simgrid::s4u::MailboxPtr thismb;
	string nameNode;
	HdfsClient(simgrid::s4u::MailboxPtr nnmb,simgrid::s4u::MailboxPtr thismb);
	bool writeFile(HdfsFile *h);
	bool read(HdfsFile* hr);
	virtual ~HdfsClient();
};

#endif /* HDFS_HDFSCLIENT_H_ */
