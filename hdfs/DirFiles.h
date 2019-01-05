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
static	int64_t dirIds;
	string dirName;
	map<string,HdfsFile *>* Files;

	int64_t id;

	DirFiles(string dir);

	virtual ~DirFiles();
};

#endif /* HDFS_DIRFILES_H_ */
