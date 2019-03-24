/*
 * MRClient.cpp
 *
 *  Created on: Feb 4, 2019
 *      Author: alpha
 */

#include "MRClient.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(mrclient, "Messages specific for this example");
MRClient::MRClient(std::vector<std::string> args) {

	thisName = simgrid::s4u::this_actor::get_host()->get_name() + "_"
			+ simgrid::s4u::this_actor::get_name();

	xbt_assert(args.size() > 0, "the arguments must be more than one");
	this->nameNodeName = args[1];
	this->rMangerName = args[2];
	rManager = Mailbox::by_name(rMangerName);

	nnmb = simgrid::s4u::Mailbox::by_name(nameNodeName);

	thismb = simgrid::s4u::Mailbox::by_name(thisName);
	thismb->set_receiver(Actor::self());

}
MRClient::MRClient(string argv) {


}

void MRClient::sendJob(JobInfo* job) {
	Message *m = new Message(msg_type::cl_rm_send_job, thismb->get_name(),
			rMangerName, 1, job);
	XBT_INFO("send job mssage %s", rManager->get_name().c_str());
	rManager->put(m, 1522);
	XBT_INFO("send job mssage");
}
void MRClient::operator()() {
	int jobsNum=4;
	vector<JobInfo*> jVector;
	for (int i = 0; i < jobsNum; i++) {
		JobInfo*job = new JobInfo();
		initJob(job);
		this->writeDate(job);
		jobs.push_back(job->jid);
		jVector.push_back(job);
	}
//send requests to rManager
	for (int i = 0; i < jobsNum; i++) {
		sendJob(jVector.at(i));
	}

	for (int i = 0; i < jobsNum; i++) {
		Message*m2 = static_cast<Message*>(thismb->get());
		if (m2->type != msg_type::finish_job) {
			XBT_INFO("error client mapreduce finish job");
			exit(1);
		}
	}
	XBT_INFO("finish job message send end of simul mssage");
	Message *endm = new Message(msg_type::end_of_simulation, thismb->get_name(),
			nameNodeName, 1, nullptr);

	nnmb->put(endm, 1522);
	Message *endm2 = new Message(msg_type::end_of_simulation,
			thismb->get_name(), rMangerName, 1, nullptr);
	rManager->put(endm2, 1522);

//TODO receive ack from client that the job is complete

//Message *ends = new Message(msg_type::end_of_simulation,
//	simgrid::s4u::this_actor::get_name(),
	//	rManager->get_name(),0,nullptr);
//	rManager->put(ends, 1522);
}
void MRClient::initJob(JobInfo* job) {
	string s;

	job->user = thisName;

	job->jobStatus = "waiting";
	job->jobName = "job_"+to_string(job->jid);

	//algorithm
	job->compressionCost = 1.0;
	job->uncompressionCost = 1.0;
	job->compressionSize = 1.0;


	//map cost for tera sort equal to number of record in chnk
	job->chunkSize=128*1024*1024;
	job->recordSize=100;
	job->mapRecord = job->chunkSize/job->recordSize;

	job->mapCost = job->mapRecord*10;//10 is num keys per record so the cost is num record * num keys ber record
	job->mapSize = job->chunkSize;

	job->mapOutAvRecordSize = 12.0;
	job->mapOutRecord=job->mapRecord*10;


	job->combineCost = 1.0;
	job->combineSize = 1.0;
	job->combineRecords = 1.0;
	job->combineGroups = 28.0;
	job->combineOutAvRecordSize = 1.0;
	job->combineOutAvRecordSize_add = 0.0;
	job->reduceCost = 80.0;
	job->reduceRecords = 0.001235;
	job->reduceOutAvRecordSize = 9.8889;
	//data

	job->recordsNumPerChunk = 2500;
	job->numOfFiles = 100;
	job->maxFileSize = 256 * 1024 * 1024;
	job->minFileSize = 128 * 1024 * 1024;

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
	job->numberOfReducers = 3;

	job->useCombiner = false;
	job->useCompression = false;
}
void MRClient::writeDate(JobInfo *job) {
	HdfsClient* hd = new HdfsClient(nnmb, thismb);

	for (int i = 0; i < job->numOfFiles; i++) {

		HdfsFile* fi = new HdfsFile(job->jobName, std::to_string(i),
				RandClass::getRand(job->minFileSize, job->maxFileSize));
		hd->writeFile(fi);
	}
	string* payload = &job->jobName;
	Message *ms = new Message(msg_type::cl_nn_re_dir, thismb->get_name(),
			nameNodeName, 0, payload);
	nnmb->put(ms, 1522);
	XBT_INFO("before get dir");
	Message * res = static_cast<Message*>(thismb->get());
	XBT_INFO("after get dir");
	DirFiles *dirF = static_cast<DirFiles *>(res->payload);
	job->dir = dirF;

	delete ms;
}
MRClient::~MRClient() {
	// TODO Auto-generated destructor stub
}

