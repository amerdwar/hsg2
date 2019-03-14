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
	double mapCost = 10000.0;
	double mapSize = 5.769283;
	double mapRecord = 50.0;
	double mapOutAvRecordSize = 12.0;
	double combineCost = 1.0;
	double combineSize = 1.0;
	double combineRecords = 1.0;
	double combineGroups = 1.0;
	double combineOutAvRecordSize = 1.0;
	double combineOutAvRecordSize_add = 0.0;
	double reduceCost = 80.0;
	double reduceRecords = 0.001235;
	double reduceOutAvRecordSize = 9.8889;
//data
	DirFiles* dir=nullptr;
	double recordsNumPerChunk=100;
	int numOfFiles=10;
	int64_t maxFileSize= 1*1024*1024*128;
	int64_t minFileSize =1*1024*1024*128;

//other
	double ioSortFactor = 10;//numb of spill to be merge in single step
	double ioSortMb = 100.0;//size of map buffer in mb
	double ioSortSpillPercent = 0.8;//the threshold to trigger spilling
	int mapCombineMinspills=3;//if the spill number less than this var so we do not need to run compiner
	double ioSortRecordPercent = 0.05;

	double mapredChildJavaOpts = 200;
	int mapredInmemMergeThreshold = 1000;
	double mapredJobReduceInputBufferPercent = 0.0;
	double mapredJobShuffleInputBufferPercent = 0.7;
	double mapredJobShuffleMergePercent = 0.66;
	double mapReduceParallelCopies = 5;
	double memoryLimit = 1.4138736E8;

	double numberOfMappers = 60;
	double numberOfReducers = 1;

	bool useCombiner = false;
	bool useCompression = false;

	JobInfo();
	JobInfo *copy();
	virtual ~JobInfo();
private:
	static int64_t jobIds;
};

#endif /* MAPREDUCE_JOBINFO_H_ */
