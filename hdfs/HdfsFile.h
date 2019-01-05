/*
 * File.h
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#ifndef HDFS_HDFSFILE_H_
#define HDFS_HDFSFILE_H_
#include "Chunk.h"
#include <string>
#include <vector>
using namespace std;
class HdfsFile {
public:


vector<Chunk*> *chunks=new vector<Chunk*>();

	HdfsFile(string dir,string name,int64_t size);

	virtual ~HdfsFile();

	string dir;

	string name;

	int64_t size;
	int64_t id;
private:
	static int64_t fileId;
};

#endif /* HDFS_HDFSFILE_H_ */
