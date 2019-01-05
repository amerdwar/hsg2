/*
 * File.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#include "HdfsFile.h"


HdfsFile::~HdfsFile() {
	// TODO Auto-generated destructor stub
}
/**
 * @brief constructor to create new file opject
 * @param #dir the dir of the file ,#name the name of the file,#size the size of the file in bytes
 *
 */

HdfsFile::HdfsFile(string dir,string name,int64_t size){
	this->dir=dir;
	this->name=name;
	this->size=size;
    this->id=fileId++;
}
int64_t HdfsFile::fileId=0;


