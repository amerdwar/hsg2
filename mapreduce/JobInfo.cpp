/*
 * JobInfo.cpp
 *
 *  Created on: Feb 2, 2019
 *      Author: alpha
 */

#include "JobInfo.h"

JobInfo::JobInfo() {
	// TODO Auto-generated constructor stub

}
JobInfo * JobInfo::copy(){
	JobInfo *j=new JobInfo();
	j-> jobStatus=this->jobStatus;
	j-> jobName = this->jobName;

//algorithm
	j-> compressionCost = this->compressionCost;
	j-> uncompressionCost = this->uncompressionCost;
	j-> compressionSize = this->compressionSize;
	j-> mapCost = this-> mapCost ;
	j-> mapSize = this->mapSize;
	j-> mapRecord =this->mapRecord;
	j-> mapOutAvRecordSize = this->mapOutAvRecordSize;
	j-> combineCost = this->combineCost;
	j-> combineSize = this->combineSize;
	j-> combineRecords = this->combineRecords;
	j-> combineGroups = this->combineGroups;
	j-> combineOutAvRecordSize = this->combineOutAvRecordSize;
	j-> combineOutAvRecordSize_add = this->combineOutAvRecordSize_add;
	j-> reduceCost = this->reduceCost;
	j-> reduceRecords = this->reduceRecords;
	j-> reduceOutAvRecordSize = this->reduceOutAvRecordSize;
//data
	j-> dirName=this->dirName;
	j-> recordsNumPerChunk=this->recordsNumPerChunk;
	j-> numOfFiles=this->numOfFiles;
	j-> maxFileSize=this->maxFileSize;
	j-> minFileSize=this->minFileSize;

//other
	j-> ioSortFactor = this->ioSortFactor;
	j-> ioSortMb = this->ioSortMb;
	j-> ioSortRecordPercent = this->ioSortRecordPercent;
	j-> ioSortSpillPercent = this->ioSortSpillPercent;

	j-> mapredChildJavaOpts = this->mapredChildJavaOpts;
	j-> mapredInmemMergeThreshold = this->mapredInmemMergeThreshold;
	j-> mapredJobReduceInputBufferPercent = this->mapredJobReduceInputBufferPercent;
	j-> mapredJobShuffleInputBufferPercent = this->mapredJobShuffleInputBufferPercent;
	j-> mapredJobShuffleMergePercent = this->mapredJobShuffleMergePercent;
	j-> mapReduceParallelCopies = this->mapReduceParallelCopies;
	j-> memoryLimit = this->memoryLimit;

	j-> numberOfMappers = this->numberOfMappers;
	j-> numberOfReducers = this->numberOfReducers;

	j-> useCombiner = this->useCombiner;
	j-> useCompression = this->useCompression;


return j;
}

JobInfo::~JobInfo() {
	// TODO Auto-generated destructor stub
}

