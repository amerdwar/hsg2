/*
 * JobInfo.h
 *
 *  Created on: Feb 2, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_JOBINFO_H_
#define MAPREDUCE_JOBINFO_H_
#include <string>
using namespace std;
class JobInfo {
public:
	string jobStatus="waiting";
	string jobName = "job";

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
	string dirName;
	double recordsNumPerChunk;
	int numOfFiles;
	int64_t maxFileSize;
	int64_t minFileSize;

//other
	double ioSortFactor = 10;
	double ioSortMb = 100.0;
	double ioSortRecordPercent = 0.05;
	double ioSortSpillPercent = 0.8;

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
	virtual ~JobInfo();
};

#endif /* MAPREDUCE_JOBINFO_H_ */
