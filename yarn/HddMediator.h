/*
 * HddMediator.h
 *
 *  Created on: Feb 25, 2019
 *      Author: alpha
 */

#ifndef YARN_HDDMEDIATOR_H_
#define YARN_HDDMEDIATOR_H_
#include "simgrid/s4u.hpp"
#include "../hdfs/DirFiles.h"
#include "../hdfs/HdfsFile.h"
#include  "../hdfs/NameNode.h"
#include "../messages/Message.h"
using namespace simgrid::s4u;
class HddMediator {
public:
	string dataNodeName;

	string task,sender;
	Mailbox* dataNode,*thismb;
	int parallelCopiers=5;
	int freeCopiers;
	int numReadReq=0;
	HddMediator(string dataNodeName,string sender,string task);
	Chunk*  writeCh(int64_t size);
	Chunk* writeCh_async(int64_t size) ;
	Chunk* readChsWrExe(vector<Chunk*>* vch,double size ,double exeF) ;
	void readCh(Chunk* ch);
	void deleteCh(Chunk*ch);
	void deleteChunkS(vector<Chunk*>* vch) ;

	virtual ~HddMediator();
};

#endif /* YARN_HDDMEDIATOR_H_ */
