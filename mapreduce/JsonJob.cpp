/*
 * JsonJob.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: alpha
 */

#include "JsonJob.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(jsonjob, "Messages specific for this example");
JsonJob::JsonJob() {
	// TODO Auto-generated constructor stub

}

JobInfo* JsonJob::getJobFromJson(string file){
JobInfo* j=new JobInfo();
Json::Value jobV;
   std::ifstream jsonFile(file);
   jsonFile >> jobV;

   	j-> jobStatus="waiting";
   	j-> jobName = jobV["jobName"].asString()+to_string(j->jid);

   //algorithm
   	j-> compressionCost = jobV["compressionCost"].asDouble();
   	j-> uncompressionCost =jobV["uncompressionCost"].asDouble();
   	j-> compressionSize = jobV["compressionSize"].asDouble();

   	j-> mergeCost = jobV["mergeCost"].asInt64();
   	j-> mapCost = jobV["mapCost"].asInt64();

   	j->recordSize=jobV["recordSize"].asInt64();

   	j->mapOutRecords=jobV["mapOutRecords"].asInt64();
   	j-> mapOutAvRecordSize = jobV["mapOutAvRecordSize"].asInt64();


   	j-> combineCost = jobV["combineCost"].asInt64();

   	j-> combineGroups = jobV["combineGroups"].asInt64();
   	j-> combineOutAvRecordSize = jobV["combineOutAvRecordSize"].asInt64();

   	j-> reduceCost = jobV["reduceCost"].asInt64();
   	j-> reduceRecords = jobV["reduceRecords"].asDouble();
   	j-> reduceOutAvRecordSize =jobV["reduceOutAvRecordSize"].asInt64();
   //data
   	j-> numOfFiles=jobV["numOfFiles"].asInt();
   	j-> maxFileSize=jobV["maxFileSize"].asInt64();
   	j-> minFileSize=jobV["minFileSize"].asInt64();

   //other
   	j-> ioSortFactor = jobV["ioSortFactor"].asDouble();
   	j-> ioSortMb = jobV["ioSortMb"].asDouble();

   	j-> ioSortSpillPercent = jobV["ioSortSpillPercent"].asDouble();
j->mapredJobReduceInputBufferPercent=jobV["mapredJobReduceInputBufferPercent"].asDouble();
   	j-> mapredJobShuffleMergePercent = jobV["mapredJobShuffleMergePercent"].asDouble();

   	j-> mapReduceParallelCopies = jobV["mapReduceParallelCopies"].asInt();
   	j-> memoryLimit = jobV["memoryLimit"].asDouble();

//   	j-> numberOfMappers = jobV[""]; set by app master as the num of chunks
   	j-> numberOfReducers =jobV["numberOfReducers"].asInt();

   	j-> useCombiner = jobV["useCombiner"].asBool();
   	j-> useCompression = jobV["useCompression"].asBool();
j->ctr->jName=j->jobName;

string ss=jobV.toStyledString();

XBT_INFO("%s",ss.c_str());



return j;
}
JsonJob::~JsonJob() {
	// TODO Auto-generated destructor stub
}

