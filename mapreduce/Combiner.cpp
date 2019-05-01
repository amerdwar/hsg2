/*
 * Combiner.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: alpha
 */

#include "Combiner.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(combiner, "Messages specific for this example");
void Combiner::mergeSpilles(vector<spill*>* v) {

	vector<spill*>* resV = new vector<spill*>();

	int num = v->size();
	if (num < mapCombineMinspills)
		return;

	int n = 0;
	while (true) {
		n = v->size();
		int l = n - ioSortFactor;
		if (l <= 0) {
			// merge from 0 to factor; and return one spill in resV

			merge(v, 0, n - 1,true);//true so this is the last merge task => compress spills
			return;
		} else if (l < ioSortFactor) {
			int t = n - l;
			l = n - t + 1;
//TODO mege from 0 to l-1 erase and push one spill
			merge(v, 0, l - 1,false);
		} else {
//TODO merge from 0 to iosortfactor and push one spill
			merge(v, 0, ioSortFactor - 1,false);
		}

	}

}
Combiner::Combiner(JobInfo* job, string dataNode, string taskName) {
	this->job = job;
	this->groups = job->combineGroups;
	this->ioSortFactor = job->ioSortFactor;
	this->ioSortMb = job->ioSortMb;
	this->ioSortSpillPercent = job->ioSortSpillPercent;
	this->dataNode = dataNode;
	this->combineCost = job->combineCost;

	this->taskName = taskName;

	this->hddM = new HddMediator(dataNode, taskName, taskName);

}

int Combiner::getNumCombinedRecordes(int groups, int rec) {
	double a = 1.0 - 1.0 / groups;
	double n = (double) rec;
	return (1 - pow(a, n)) / (1 - a);

}

void Combiner::merge(vector<spill*>* v, int fIndex, int lIndex,bool isLast) {
	int recNum = 0;
	//calculate total read, write, cpu costs
	vector<Chunk*>* vch = new vector<Chunk*>();
	for (int i = fIndex; i <= lIndex; i++) {
		vch->push_back(v->at(i)->ch);
		recNum += v->at(i)->records;
	}

	for (int i = fIndex; i <= lIndex; i++) {
		v->erase(v->begin());
	}

	int64_t lastRecNum = this->combine(recNum);
	int64_t recSize = 0;

	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, (double) lastRecNum);
	double exeF = 0;

	double comp_cost=0;
	if(isLast){
	if(job->useCompression)//so compress here
		comp_cost=(double)lastRecNum*job->compressionCost;
	else
		comp_cost=0;

	}

	if (job->useCombiner) {
		recSize = job->combineOutAvRecordSize;
		//the cost of combine and merge
		exeF =
				(double) (recNum * job->combineCost
						+ lastRecNum * job->mergeCost)+comp_cost;
	} else {
		exeF = (double) (recNum * job->mergeCost)+comp_cost;
		recSize = job->mapOutAvRecordSize;
	}

	int64_t lastSize = lastRecNum * recSize;

	if(isLast&&job->useCompression){
		XBT_INFO("before compress ch %s ",to_string(lastSize).c_str());
		lastSize=(int64_t)(lastSize*job->compressionSize);//compress
	XBT_INFO("after compress ch %s ",to_string(lastSize).c_str());


	}
	Chunk* lastCh = hddM->readChsWrExe(vch, lastSize, exeF);
	XBT_INFO("after write ch ");
	spill* lastSpill = new spill();
	lastSpill->ch = lastCh;
	lastSpill->records = lastRecNum;

	v->push_back(lastSpill);

}
Combiner::~Combiner() {
	// TODO Auto-generated destructor stub
}

int64_t Combiner::combine(int64_t recNum) {
	int64_t combinedRecs = 0;
	if (job->useCombiner) {

		combinedRecs = getNumCombinedRecordes(job->combineGroups, recNum);
		//XBT_INFO("in compiner ,num rec is %i old is %i", combinedRecs,recNum);

	} else {
		combinedRecs = recNum;
		//	XBT_INFO(" in compiner  no co ,num rec is %i", combinedRecs);
	}
	return combinedRecs;

}

void Combiner::mergeReduceSpilles(vector<spill*>* v) {

	vector<spill*>* resV = new vector<spill*>();

	int num = v->size();

	int n = 0;
	while (true) {
		n = v->size();
		int l = n - ioSortFactor;
		if (l <= 0) {
			//TODO merge from 0 to n; and return one spill in resV
			mergeReduce(v, 0, n - 1);
			return;
		} else if (l < ioSortFactor) {
			int t = n - l;
			l = n - t + 1;
//TODO mege from 0 to l-1 erase and push one spill
			mergeReduce(v, 0, l - 1);
		} else {
//TODO merge from 0 to iosortfactor and push one spill
			mergeReduce(v, 0, ioSortFactor - 1);
		}

	}

}

void Combiner::mergeReduce(vector<spill*>* v, int fIndex, int lIndex) {
	int64_t recNum = 0;

	vector<Chunk*>* vch = new vector<Chunk*>();
	for (int i = fIndex; i <= lIndex; i++) {

		if (!v->at(i)->isInMem) { //if in memory do not read it
			v->at(i)->ch->clinetMB = Mailbox::by_name(taskName);
			//hddM->readCh(v->at(i)->ch);
			//hddM->deleteCh(v->at(i)->ch);
			vch->push_back(v->at(i)->ch);
		}

		//v->erase(v->begin() + i);

		recNum += v->at(i)->records;
	}
	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, recNum);

	for (int i = fIndex; i <= lIndex; i++) {
		v->erase(v->begin());
	}


	int64_t lastRecNum = this->combine(recNum);
	int64_t recSize = 0;

	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, (double) lastRecNum);
	double exeF = 0;
	if (job->useCombiner) {
		recSize = job->combineOutAvRecordSize;
		//the cost of combine and merge
		exeF =
				(double) (recNum * job->combineCost
						+ lastRecNum * job->mergeCost);
	} else {
		exeF = (double) (recNum * job->mergeCost);
		recSize = job->mapOutAvRecordSize;
	}

	int64_t lastSize = lastRecNum * recSize;


	XBT_INFO("beforrrrrrr write ch");
	Chunk* lastCh = hddM->readChsWrExe(vch, lastSize, exeF);
	XBT_INFO("after ****************write ch");
	spill* lastSpill = new spill();
	lastSpill->ch = lastCh;
	lastSpill->records = recNum;

	v->push_back(lastSpill);

}
