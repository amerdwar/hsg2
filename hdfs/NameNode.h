/*
 * NameNode.h
 *
 *  Created on: Dec 27, 2018
 *      Author: alpha
 */

#ifndef HDFS_NAMENODE_H_
#define HDFS_NAMENODE_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "simgrid/kernel/routing/ClusterZone.hpp"
#include "simgrid/s4u.hpp"
#include "../distributions/RandClass.h"
#include "DirFiles.h"
#include "../messages/Message.h"
#include "HdfsFile.h"


using namespace std;
using namespace simgrid::s4u;

class NameNode {
public:
	//the NameNode data members
static int replicatinNum;
string nameNodeName;
//16777216 16mb
//134217728 128mb
static int64_t chunkSize;//the size in byte and this value equal to 128 mb
map<string,DirFiles *>* allDires ;
vector<simgrid::kernel::routing::ClusterZone*> racks;//this variable must be initialized in main and we can get the hosts like this     std::vector<simgrid::s4u::Host*> hosts = c->get_all_hosts();
map<MailboxPtr,vector<Chunk *>>* dataNodes;//data nodes with their chunks
explicit	NameNode(std::vector<std::string> args);
	simgrid::s4u::Host* randomHostInRack(simgrid::kernel::routing::ClusterZone*);
	simgrid::s4u::Host* randomHostInRackExceptHost(simgrid::kernel::routing::ClusterZone* rack,string host);
	bool hdfs_write(string dir,string file,int64_t file_size,simgrid::s4u::MailboxPtr sender);
	std::vector<HdfsFile>* getDirFiles(string dir);
	simgrid::s4u::Host* randHostExcept( simgrid::kernel::routing::ClusterZone* rack,std::vector<string>,int chindex);
	void getFileChunks();
	double hdfs_read();
	void operator()();

	virtual ~NameNode();
private:
	simgrid::s4u::MailboxPtr mailbox;
};

#endif /* HDFS_NAMENODE_H_ */
