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
this->chGenId=this->chId;
this->nodes=new  vector<simgrid::s4u::MailboxPtr>();
}
Chunk* Chunk::copy(){
Chunk* cc=new Chunk(dirName,fileName,fileId,size);
	cc->nodes=this->nodes;
	cc->storage=storage;
	cc->clinetMB=clinetMB;
	cc->chId=chId;
	cc->writeIndex=writeIndex;
	cc->chGenId=this->chId;
	return cc;
}
 int64_t Chunk::chIds=0;
Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}

