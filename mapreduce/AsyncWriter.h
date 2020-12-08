/*
 * AsyncWriter.h
 *
 *  Created on: May 13, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_ASYNCWRITER_H_
#define MAPREDUCE_ASYNCWRITER_H_
#include <simgrid/s4u.hpp>
#include <string.h>
#include "../hdfs/Chunk.h"
#include <vector>

#include "../messages/Message.h"
using namespace std;
using namespace simgrid::s4u;
class AsyncWriter {
public:
	string thisName,dataNode,parent;
	Mailbox* thismb,*dataNodeMb;
Chunk* ch;

	explicit AsyncWriter(string name,string dataNode,string parent,Chunk* ch);
	void operator()();

	virtual ~AsyncWriter();
};

#endif /* MAPREDUCE_ASYNCWRITER_H_ */
