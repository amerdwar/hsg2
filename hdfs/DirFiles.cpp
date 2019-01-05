/*
 * DirFiles.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#include "DirFiles.h"
/**
 * @brief the constructor of DirFiles
 * @param #dir the name of the direction

 */

DirFiles::DirFiles(string dir) {

	this->dirName=dir;

	Files =new map<string,HdfsFile*>();
this->id=++DirFiles::dirIds;
}

DirFiles::~DirFiles() {
	// TODO Auto-generated destructor stub
	delete Files;
}

int64_t DirFiles:: dirIds=0;


