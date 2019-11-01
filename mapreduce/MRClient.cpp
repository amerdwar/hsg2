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

	XBT_INFO("in mr client");
	xbt_assert(args.size() > 0, "the arguments must be more than one");
	this->nameNodeName = args[1];
	this->rMangerName = args[2];
	XBT_INFO("in mr client %s",this->rMangerName.c_str());


	rManager = Mailbox::by_name(rMangerName);
	XBT_INFO("in mr client");
	nnmb = simgrid::s4u::Mailbox::by_name(nameNodeName);

	thismb = simgrid::s4u::Mailbox::by_name(thisName);
	thismb->set_receiver(Actor::self());
jsonJob=new  JsonJob();
XBT_INFO("in mr client");
}



void MRClient::sendJob(JobInfo* job) {
	Message *m = new Message(msg_type::cl_rm_send_job, thismb->get_name(),
			rMangerName, 1, job);
	job->ctr->addToCtr(ctr_t::JOB_START_TIME,Engine::get_clock());
	//XBT_INFO("send job mssage %s", rManager->get_name().c_str());
	rManager->put(m, 1522);
	//XBT_INFO("send job mssage");
}
void MRClient::operator()() {
	// path p("../resources/jobs");

	XBT_INFO("in mr client");
vector<string> jNames= getAllJobs();



	int jobsNum=jNames.size();
	vector<JobInfo*> jVector;

	for (int i = 0; i < jobsNum; i++) {
		JobInfo*job = jsonJob->getJobFromJson(jNames.at(i));


		job->user=thisName;
		//initJob(job);
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
		XBT_INFO("recive finish from lj;lkj;gfguhjlk;jhgfj");
		if (m2->type != msg_type::finish_job) {
			XBT_INFO("error client mapreduce finish job");
			exit(1);
		}
		JobInfo * jj = static_cast<JobInfo*>(m2->payload);
		double startT,stopT,avgMap,avgReduce,avgSh;
		stopT=Engine::get_clock();

		//calc job time
		jj->ctr->addToCtr(ctr_t::JOB_STOP_TIME,stopT);
		startT=jj->ctr->getCtr(JOB_START_TIME);
		//calc mappers avg time
		jj->ctr->setCtr(ctr_t::JOB_TOTAL_TIME,stopT-startT);
		avgMap=jj->ctr->getCtr(avMappersTime);
		jj->ctr->setCtr(ctr_t::avMappersTime,avgMap/jj->numberOfMappers);
		//calc reducers avg time
		jj->ctr->setCtr(ctr_t::JOB_TOTAL_TIME,stopT-startT);


		avgReduce=jj->ctr->getCtr(avReducersTime);
		jj->ctr->setCtr(ctr_t::avReducersTime,avgReduce/jj->numberOfReducers);


		avgSh=jj->ctr->getCtr(SHUFFLE);
		jj->ctr->setCtr(ctr_t::SHUFFLE,avgSh/jj->numberOfReducers);

		jj->ctr->printCtrs();
	}
	XBT_INFO("finish job message send end of simul mssage");
	Message *endm = new Message(msg_type::end_of_simulation, thismb->get_name(),
			nameNodeName, 1, nullptr);

	nnmb->put(endm, 1522);
	Message *endm2 = new Message(msg_type::end_of_simulation,
			thismb->get_name(), rMangerName, 1, nullptr);
	rManager->put(endm2, 1522);

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

	//map cost for tera sort equal to number of record in chunk
	//job->chunkSize=NameNode::chunkSize;
	job->recordSize=100;
	//job->mapRecords = 0;the records number is the size/record size > we calculate this in mapper

	job->mapCost = 10;//10 is num keys per record so the cost is num record * num keys ber record
//	job->mapSize = job->chunkSize;

	job->mapOutAvRecordSize = 12;
	job->mapOutRecords=10; //there is out record per input record


	job->combineCost = 1;
	job->combineSize = 1;
	//job->combineRecords = 1;
	job->combineGroups = 28;
	job->combineOutAvRecordSize = 1000;


	//job->combineOutAvRecordSize_add = 0;
	job->reduceCost = 80;
	job->reduceRecords = 0.1;
	job->reduceOutAvRecordSize = 9;
	//data

	job->recordsNumPerChunk = 2500;
	job->numOfFiles = 200;
	job->maxFileSize = 200 * 1024 * 1024;
	job->minFileSize = 200 * 1024 * 1024;

	//other
	job->ioSortFactor = 4;
	job->ioSortMb = 100;
	//job->ioSortRecordPercent = 0.05;
	job->ioSortSpillPercent = 0.8;

//	job->mapredChildJavaOpts = 200;
	//job->mapredInmemMergeThreshold = 1000;//amount of memory to spill after <not used
	//job->mapredJobReduceInputBufferPercent = 0.0;
	//job->mapredJobShuffleInputBufferPercent = 0.7;//the percent of heap used for copy map output
	job->mapredJobShuffleMergePercent = 0.66;//the threshold to spill
	job->mapReduceParallelCopies = 5;
	job->memoryLimit = 1024*1024*1024;//1 GB of memory for reducer

	job->numberOfMappers = 1;
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
	//XBT_INFO("before get dir");
	Message * res = static_cast<Message*>(thismb->get());
	//XBT_INFO("after get dir");
	DirFiles *dirF = static_cast<DirFiles *>(res->payload);
	job->dir = dirF;



	delete ms;
}
MRClient::~MRClient() {
	// TODO Auto-generated destructor stub
}

vector<string> MRClient::getAllJobs(){
	vector<string> jNames;

	system("ls resources/jobs > resources/jobs/ttem.txt");

    std::ifstream file("resources/jobs/ttem.txt");
    std::string str;
    while (std::getline(file, str))
    {
        string nstr="resources/jobs/"+str;
        if(nstr.find("json")!=string::npos)
        jNames.push_back(nstr);
    }
file.close();
system("rm resources/jobs/ttem.txt");

	return jNames;
}

TEST(mrclient,true){

//ASSERT_EQ(36.0, 36.0);
}
