/*
 * Chunk.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#include "Chunk.h"

Chunk::Chunk(string dirN,string fileN,int64_t fileId,int64_t fileSize) {
	// TODO Auto-generated constructor stub
this->chId=++chIds;
this->size=fileSize;
this->fileId=fileId;
this->dirName=dirN;
this->fileName=fileN;

this->nodes=new  vector<simgrid::s4u::MailboxPtr>();
}
 int64_t Chunk::chIds=0;
Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}

