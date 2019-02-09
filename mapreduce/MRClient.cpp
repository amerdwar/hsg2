/*
 * MRClient.cpp
 *
 *  Created on: Feb 4, 2019
 *      Author: alpha
 */

#include "MRClient.h"

MRClient::MRClient(std::vector<std::string> args) {
	job = new JobInfo();
	initJob();
	xbt_assert(args.size() > 0, "the arguments must be more than one");
	this->nameNodeName = args[1];
	this->rMangerName = args[2];
	rManager = Mailbox::by_name(rMangerName);

	nnmb = simgrid::s4u::Mailbox::by_name(nameNodeName);
	thismb = simgrid::s4u::Mailbox::by_name(
			simgrid::s4u::this_actor::get_host()->get_name() + "_"
					+ simgrid::s4u::this_actor::get_name());
	thismb->set_receiver(Actor::self());

}
MRClient::MRClient(string argv) {
	// TODO Auto-generated constructor stub
	job = new JobInfo();
}

void MRClient::sendJob(JobInfo* j) {

}
void MRClient::operator()() {
this->writeDate();
//send request to rManager
Message *m=new Message(msg_type::cl_rm_send_job,thismb->get_name(),rMangerName,1,job);
rManager->put(m,1522);
//TODO receive ack from client that the job is complete
}
void MRClient::initJob() {
	job->jobStatus = "waiting";
	job->jobName = "job";

	//algorithm
	job->compressionCost = 1.0;
	job->uncompressionCost = 1.0;
	job->compressionSize = 1.0;
	job->mapCost = 10000.0;
	job->mapSize = 5.769283;
	job->mapRecord = 50.0;
	job->mapOutAvRecordSize = 12.0;
	job->combineCost = 1.0;
	job->combineSize = 1.0;
	job->combineRecords = 1.0;
	job->combineGroups = 1.0;
	job->combineOutAvRecordSize = 1.0;
	job->combineOutAvRecordSize_add = 0.0;
	job->reduceCost = 80.0;
	job->reduceRecords = 0.001235;
	job->reduceOutAvRecordSize = 9.8889;
	//data
	job->dirName = "dir1";
	job->recordsNumPerChunk = 2500;
	job->numOfFiles = 25;
	job->maxFileSize = 1 * 1024 * 1024 * 1024;
	job->minFileSize = 7 * 1024 * 1024 * 1024;

	//other
	job->ioSortFactor = 10;
	job->ioSortMb = 100.0;
	job->ioSortRecordPercent = 0.05;
	job->ioSortSpillPercent = 0.8;

	job->mapredChildJavaOpts = 200;
	job->mapredInmemMergeThreshold = 1000;
	job->mapredJobReduceInputBufferPercent = 0.0;
	job->mapredJobShuffleInputBufferPercent = 0.7;
	job->mapredJobShuffleMergePercent = 0.66;
	job->mapReduceParallelCopies = 5;
	job->memoryLimit = 1.4138736E8;

	job->numberOfMappers = 60;
	job->numberOfReducers = 1;

	job->useCombiner = false;
	job->useCompression = false;
}
void MRClient::writeDate() {
	HdfsClient* hd = new HdfsClient(nnmb, thismb);
	for (auto i : job->numOfFiles) {

		HdfsFile* fi = new HdfsFile(job->dirName, "file" + i,
				RandClass::getRand(job->minFileSize, job->maxFileSize));
		hd->writeFile(fi);
	}
}
MRClient::~MRClient() {
	// TODO Auto-generated destructor stub
}

