/*
 * YarnScheduler.cpp
 *
 *  Created on: Feb 9, 2019
 *      Author: alpha
 */

#include "YarnScheduler.h"

YarnScheduler::YarnScheduler(int numAllCon, std::map<string, int> con) {
	// TODO Auto-generated constructor stub
	this->numAllCon = numAllCon;
	this->containers = con;

}
void YarnScheduler::addReq(allocateReq allr) {
	allReq.push_back(allr); //all req is vector so we push back and serve first then erase first

}
std::vector<allocateRes> YarnScheduler::allocate() {
	switch (this->type) {
	case sch_type::fifo: {
		return this->fifo();
		break;
	}
	case sch_type::fair: {
		return this->fair();
		break;
	}
	case sch_type::capacity: {
		return this->capacity();
		break;
	}
	default: {
		return this->fifo();
		break;
	}

	}
}
void YarnScheduler::freeCon(string host) {
	containers.at(host)++;}
std::vector<allocateRes> YarnScheduler::fifo() {
	std::vector<allocateRes> a;

	if (allReq.size() != 0) { //serve req

		for (int i = 0; i < allReq.size(); i++) { // start serve allocation request from the first one
			for (int fi = allReq.at(i).fIndex;
					fi < allReq.at(i).dir.Files->size(); fi++) {

				for (int c = allReq.at(i).chIndex;
						c
								< allReq.at(i).dir.Files->at(std::to_string(fi))->chunks->size();
						c++) {
					//num of nodes that the chunk on them
					int numNode =
							allReq.at(i).dir.Files->at(std::to_string(fi))->chunks->at(
									c)->nodes->size();
					for (int n = 0; n < numNode; n++) {
						MailboxPtr dataNode = allReq.at(i).dir.Files->at(
								std::to_string(fi))->chunks->at(c)->nodes->at(
								n);
						string dnName = dataNode->get_name();
//then we will get host name from datanode name  hostname_datanode
string hostName=dnName.substr(0,dnName.find("_"));
						if () {

						}
					}
				}
			}
		}
	}

	return a;

}
std::vector<allocateRes> YarnScheduler::fair() {
	std::vector<allocateRes> a;

	return a;
}
std::vector<allocateRes> YarnScheduler::capacity() {
	std::vector<allocateRes> a;

	return a;
}
void YarnScheduler::addJob(JobInfo job) {
	waitingJobs.push_back(job);

}
YarnScheduler::~YarnScheduler() {
	// TODO Auto-generated destructor stub
}

