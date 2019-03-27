/*
 * DirFiles.h
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#ifndef HDFS_DIRFILES_H_
#define HDFS_DIRFILES_H_
#include <string>
#include <vector>

#include "HdfsFile.h"
using namespace std;
class DirFiles {
public:
static	int64_t dirIds,chunkSize=128*1024*1024;
	string dirName;

	map<string,HdfsFile *>* Files;

	int64_t id;

	DirFiles(string dir);
	DirFiles(string dir,int64_t chSize) ;
	virtual ~DirFiles();
};

#endif /* HDFS_DIRFILES_H_ */
