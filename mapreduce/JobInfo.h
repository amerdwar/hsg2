/*
 * JobInfo.h
 *
 *  Created on: Feb 2, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_JOBINFO_H_
#define MAPREDUCE_JOBINFO_H_
#include <string>
#include "Counter.h"
#include "../hdfs/DirFiles.h"
using namespace std;
class JobInfo {
public:
	string jobStatus = "waiting";
	Counter* ctr;
	string jobName = "job";
	int64_t jid;
	string user;
//algorithm
	double compressionCost = 1.0;
	double uncompressionCost = 1.0;
	double compressionSize = 1.0;

	//int64_t chunkSize = 128 * 1024 * 1024;
	double recordSize = 100;//the size of map record

	int64_t mapCost = 10;//cost per record
//	int64_t mapSize = 5;//num record * record size the same as chunk size
	int64_t mapRecords = 50;//num record per chunk
	double mapOutRecords = 500;//num map out record per input record
    int64_t mergeCost=10;//cost per record
	double mapOutAvRecordSize = 12;//the size of map output
	int64_t combineCost = 1;
	int64_t combineSize = 1;//to do delete this
//	int64_t combineRecords = 1;//to do delete
	int64_t combineGroups = 1;//num of keys per spill
	double combineOutAvRecordSize = 12;
//	int64_t combineOutAvRecordSize_add = 0;//to do delete not used

	int64_t reduceCost = 80;
	double reduceRecords = 0;
	double reduceOutAvRecordSize = 9;
//dataint64_t
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
	//double ioSortRecordPercent = 0.05;

	//double mapredChildJavaOpts = 200;//to do delete
	//int mapredInmemMergeThreshold = 1000;//to do delete

	double mapredJobReduceInputBufferPercent = 0.7;//if spill > so write to disk
	//we always use as much as possible of memory so this is 0
	double mapredJobShuffleMergePercent = 0.66;//threshold to spills in memory on reducer
	int mapReduceParallelCopies = 5;//the number of copiers
	double memoryLimit = 1.4138736E8;//the memory for shuffle

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
