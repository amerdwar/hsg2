/*
 * JobInfo.cpp
 *
 *  Created on: Feb 2, 2019
 *      Author: alpha
 */

#include "JobInfo.h"

JobInfo::JobInfo() {
	// TODO Auto-generated constructor stub
	this->jid=jobIds++;
ctr=new Counter();
}
JobInfo * JobInfo::copy(){

	JobInfo *j=new JobInfo();
	j->ctr=this->ctr;
	j->mapOutRecords=this->mapOutRecords;
	j->recordSize=this->recordSize;
	//j->chunkSize=this->chunkSize;
	j->jid=this->jid;
	j-> jobStatus=this->jobStatus;
	j-> jobName = this->jobName;
j->user=this->user;
//algorithm
	j-> compressionCost = this->compressionCost;
	j-> uncompressionCost = this->uncompressionCost;
	j-> compressionSize = this->compressionSize;
	j-> mapCost = this-> mapCost ;
	//j-> mapSize = this->mapSize;
	j-> mapRecords =this->mapRecords;
	j-> mapOutAvRecordSize = this->mapOutAvRecordSize;
	j-> combineCost = this->combineCost;
	j-> combineSize = this->combineSize;
	//j-> combineRecords = this->combineRecords;
	j-> combineGroups = this->combineGroups;
	j-> combineOutAvRecordSize = this->combineOutAvRecordSize;
	//j-> combineOutAvRecordSize_add = this->combineOutAvRecordSize_add;
	j-> reduceCost = this->reduceCost;
	j-> reduceRecords = this->reduceRecords;
	j-> reduceOutAvRecordSize = this->reduceOutAvRecordSize;
//data
	j-> dir=this->dir;
	j-> recordsNumPerChunk=this->recordsNumPerChunk;
	j-> numOfFiles=this->numOfFiles;
	j-> maxFileSize=this->maxFileSize;
	j-> minFileSize=this->minFileSize;

//other
	j-> ioSortFactor = this->ioSortFactor;
	j-> ioSortMb = this->ioSortMb;
	//j-> ioSortRecordPercent = this->ioSortRecordPercent;
	j-> ioSortSpillPercent = this->ioSortSpillPercent;

//	j-> mapredChildJavaOpts = this->mapredChildJavaOpts;
	//j-> mapredInmemMergeThreshold = this->mapredInmemMergeThreshold;
	//-> mapredJobReduceInputBufferPercent = this->mapredJobReduceInputBufferPercent;
	//j-> mapredJobShuffleInputBufferPercent = this->mapredJobShuffleInputBufferPercent;
	j-> mapredJobShuffleMergePercent = this->mapredJobShuffleMergePercent;
	j-> mapReduceParallelCopies = this->mapReduceParallelCopies;
	j-> memoryLimit = this->memoryLimit;

	j-> numberOfMappers = this->numberOfMappers;
	j-> numberOfReducers = this->numberOfReducers;

	j-> useCombiner = this->useCombiner;
	j-> useCompression = this->useCompression;


return j;
}
int64_t JobInfo::jobIds=0;
JobInfo::~JobInfo() {
	// TODO Auto-generated destructor stub
}

