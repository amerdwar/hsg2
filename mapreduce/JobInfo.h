/*
 * JobInfo.h
 *
 *  Created on: Feb 2, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_JOBINFO_H_
#define MAPREDUCE_JOBINFO_H_
#include <string>
#include "../hdfs/DirFiles.h"
using namespace std;
class JobInfo {
public:
	string jobStatus = "waiting";
	string jobName = "job";
	int64_t jid;
	string user;
//algorithm
	double compressionCost = 1.0;
	double uncompressionCost = 1.0;
	double compressionSize = 1.0;

	int64_t chunkSize = 128 * 1024 * 1024;
	int64_t recordSize = 100;

	int64_t mapCost = 10000;
	int64_t mapSize = 5;
	int64_t mapRecord = 50;
	int64_t mapOutRecord = 500;

	int64_t mapOutAvRecordSize = 12;
	int64_t combineCost = 1;
	int64_t combineSize = 1;
	int64_t combineRecords = 1;
	int64_t combineGroups = 1;
	int64_t combineOutAvRecordSize = 12;
	int64_t combineOutAvRecordSize_add = 0;
	int64_t reduceCost = 80;
	double reduceRecords = 0;
	int64_t reduceOutAvRecordSize = 9;
//data
	DirFiles* dir = nullptr;
	double recordsNumPerChunk = 100;
	int numOfFiles = 10;
	int64_t maxFileSize = 1 * 1024 * 1024 * 128;
	int64_t minFileSize = 1 * 1024 * 1024 * 128;

//other
	double ioSortFactor = 10; //numb of spill to be merge in single step
	double ioSortMb = 100.0; //size of map buffer in mb
	double ioSortSpillPercent = 0.8; //the threshold to trigger spilling
	int mapCombineMinspills = 3; //if the spill number less than this var so we do not need to run compiner
	double ioSortRecordPercent = 0.05;

	double mapredChildJavaOpts = 200;
	int mapredInmemMergeThreshold = 1000;
	double mapredJobReduceInputBufferPercent = 0.0;
	double mapredJobShuffleInputBufferPercent = 0.7;
	double mapredJobShuffleMergePercent = 0.66;
	int mapReduceParallelCopies = 5;
	double memoryLimit = 1.4138736E8;

	int numberOfMappers = 60;
	int numberOfReducers = 1;

	bool useCombiner = true;
	bool useCompression = false;

	JobInfo();
	JobInfo *copy();
	virtual ~JobInfo();
private:
	static int64_t jobIds;
};

#endif /* MAPREDUCE_JOBINFO_H_ */
