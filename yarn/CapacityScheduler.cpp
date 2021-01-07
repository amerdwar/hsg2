#include "CapacityScheduler.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(CapacityScheduler,
		"Messages specific for this example");

CapacityScheduler::CapacityScheduler(int numAllCon, std::map<string, int> con) {
	JsonPlatform *jp = new JsonPlatform();
	this->queus = jp->readCapacityFile();
	int conMapSize = con.size();
	int reminderOfcon = conMapSize;
	int startIndex = 0;
	std::map<string, int>::const_iterator conIT = con.begin();
	int qSize=this->queus->size();

	for (int i = 0; i <qSize; i++) {
		XBT_INFO("size is ");
		Capacity *cItem = this->queus->at(i);

		XBT_INFO("the q name is %s,the percent is %d",cItem->name.c_str(),cItem->percent);
		int temSize = (int)(cItem->percent * conMapSize / 100);
		if (temSize == 0) {
			XBT_INFO("bad capacity scheduler file");
			exit(1);
		}
		reminderOfcon -= temSize;
		if (reminderOfcon < 0) {

			XBT_INFO("bad capacity scheduler file");
			exit(1);
		}
		if (this->queus->size() - 1 == i && reminderOfcon > 0) {
			temSize += reminderOfcon;
		}
		int conCount = 0;

		std::map<string, int> res;
		for (int j = 0; j < temSize; j++) {
			res.insert(std::pair<string, int>(conIT->first, conIT->second));
			conIT++;
			conCount += conIT->second;
		}
		XBT_INFO("the size of containers %d",res.size());



		FIFOScheduler *a = new FIFOScheduler(conCount, res);
		XBT_INFO("the conCount %d",conCount);
		this->allQ.insert(std::pair<string, FIFOScheduler*>(cItem->name, a));






		XBT_INFO("end for");
	}
	XBT_INFO("after if");
//exit(1);
	this->numAllCon = numAllCon;

}
void CapacityScheduler::addReq(allocateReq *allr) {
	XBT_INFO("add req");
	//all req is vector so we push back and serve first then erase first

	this->allQ.at(allr->job->queueName)->addReq(allr);

}
std::vector<allocateRes*> CapacityScheduler::allocate() {

	std::vector<allocateRes*> resV;
	for (auto &kvp : this->allQ) {

		std::vector<allocateRes*> QItemRes = kvp.second->allocate();


		if (QItemRes.size() > 0) {
			resV.insert(resV.begin(), QItemRes.begin(), QItemRes.end());
		}


	}

	return resV;

}
void CapacityScheduler::freeCon(string host) {

	for (auto &kvp : this->allQ) {
		kvp.second->freeCon(host);

	}

	//////XBT_INFO("free container %s", host.c_str());
}

void CapacityScheduler::addJob(JobInfo *job) {

	this->allQ.at(job->queueName)->addJob(job);
}
CapacityScheduler::~CapacityScheduler() {
// TODO Auto-generated destructor stub
}

void CapacityScheduler::insertFromMapToMap(std::map<string, int> con,
		string jobName, int startIndex, int count) {
	std::map<string, int> res;
	int conCount = 0;

	for (int i = 0; i < count; i++) {

	}

	for (std::map<string, int>::const_iterator it = res.begin();
			it != res.end(); it++) {
		conCount += it->second;

	}

	FIFOScheduler *a = new FIFOScheduler(conCount, res);

	this->allQ.insert(std::pair<string, FIFOScheduler*>(jobName, a));
}

void CapacityScheduler::printRes(allocateRes *res) {

	////XBT_INFO(" fi=%i ch=%i ty=%i requester=%s", res->fIndex, res->chIndex,
	//res->type, res->requester.c_str());
}
void CapacityScheduler::printReq(allocateReq *res) {

	////XBT_INFO(" fi=%i ch=%i ty=%i requester=%s", res->fIndex, res->chIndex,
	//res->type, res->requester.c_str());
}
