/*
 * Combiner.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: alpha
 */

#include "Combiner.h"

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
			//TODO merge from 0 to factor; and return one spill in resV
			merge(v, 0, l - 1);
			return;
		} else if (l < ioSortFactor) {
			int t = n - l;
			l = n - t + 1;
//TODO mege from 0 to l-1 erase and push one spill
			merge(v, 0, l - 1);
		} else {
//TODO merge from 0 to iosortfactor and push one spill
			merge(v, 0, ioSortFactor - 1);
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

void Combiner::merge(vector<spill*>* v, int fIndex, int lIndex) {
	int recNum = 0;

	for (int i = fIndex; i <= lIndex; i++) {
		hddM->readCh(v->at(i)->ch);
		hddM->deleteCh(v->at(i)->ch);
		v->erase(v->begin() + i);
		recNum += v->at(i)->records;
	}
	for (int i = fIndex; i <= lIndex; i++) {
		v->erase(v->begin() + i);
	}
	int64_t recSize = 0;

	if (job->useCombiner)
		recSize = job->combineOutAvRecordSize;
	else
		recSize = job->mapOutAvRecordSize;



	int64_t lastSize = recNum * recSize;
	Chunk* lastCh = hddM->writeCh(lastSize);

	spill* lastSpill = new spill();
	lastSpill->ch = lastCh;
	lastSpill->records = recNum;

	v->push_back(lastSpill);

}
Combiner::~Combiner() {
	// TODO Auto-generated destructor stub
}

int64_t Combiner::combine(int64_t recNum) {
	int64_t combinedRecs = 0;
	if (job->useCombiner) {

		combinedRecs = getNumCombinedRecordes(job->combineGroups,
				recNum);
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
			//TODO merge from 0 to factor; and return one spill in resV
			merge(v, 0, l - 1);
			return;
		} else if (l < ioSortFactor) {
			int t = n - l;
			l = n - t + 1;
//TODO mege from 0 to l-1 erase and push one spill
			merge(v, 0, l - 1);
		} else {
//TODO merge from 0 to iosortfactor and push one spill
			merge(v, 0, ioSortFactor - 1);
		}

	}

}


void Combiner::mergeReduce(vector<spill*>* v, int fIndex, int lIndex) {
	int recNum = 0;

	for (int i = fIndex; i <= lIndex; i++) {
		hddM->readCh(v->at(i)->ch);
		hddM->deleteCh(v->at(i)->ch);
		v->erase(v->begin() + i);
		recNum += v->at(i)->records;
	}
	for (int i = fIndex; i <= lIndex; i++) {
		v->erase(v->begin() + i);
	}
	int64_t recSize = 0;

	if (job->useCombiner)
		recSize = job->combineOutAvRecordSize;
	else
		recSize = job->mapOutAvRecordSize;



	int64_t lastSize = recNum * recSize;
	Chunk* lastCh = hddM->writeCh(lastSize);

	spill* lastSpill = new spill();
	lastSpill->ch = lastCh;
	lastSpill->records = recNum;

	v->push_back(lastSpill);

}
