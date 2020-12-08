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
using namespace simgrid::s4u;
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
	ExecPtr exePtr=nullptr;
	simgrid::s4u::Mailbox* clinetMB=nullptr;
	vector<simgrid::s4u::Mailbox*> *nodes;
	Chunk(string dirName,string fileName,int64_t fileId,int64_t fileSize);
	bool isWritten=false;
	Chunk* copy();
	virtual ~Chunk();
private:
	static int64_t chIds;
};

#endif /* HDFS_CHUNK_H_ */
