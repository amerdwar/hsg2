/*
 * Chunk.h
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#ifndef HDFS_CHUNK_H_
#define HDFS_CHUNK_H_
#include <iostream>
#include <string>
#include <vector>
#include <simgrid/s4u.hpp>
using namespace std;
class Chunk {
public:

int chRepNum=0;//this number will increment whene send the chunk from one data node to another
	int64_t chId;
	int64_t chGenId;
	int64_t fileId;
	int64_t size;
	int writeIndex=0;// for node vector
	string fileName;
	string dirName;
	string storage;
	simgrid::s4u::MailboxPtr clinetMB=nullptr;
	vector<simgrid::s4u::MailboxPtr> *nodes;
	Chunk(string dirName,string fileName,int64_t fileId,int64_t fileSize);
	Chunk* copy();
	virtual ~Chunk();
private:
	static int64_t chIds;
};

#endif /* HDFS_CHUNK_H_ */
