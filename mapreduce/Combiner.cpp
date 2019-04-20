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
			//TODO merge from 0 to factor; and return one spill in resV

			merge(v, 0, n - 1);
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
		XBT_INFO("before read  ch %i", v->at(i)->isInMem);
		int a, b, c;
		a = v->at(i)->ch->chGenId;
		hddM->readCh(v->at(i)->ch);
		b = v->at(i)->ch->chGenId;
		XBT_INFO("after read ch ");
		hddM->deleteCh(v->at(i)->ch);

		c = v->at(i)->ch->chGenId;

		XBT_INFO("mmmmmmmmmm %i   %i    %i", a, b, c);

		recNum += v->at(i)->records;
	}

	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS,(double)recNum);

	for (int i = fIndex; i <= lIndex; i++) {
		v->erase(v->begin());

	}
	int64_t recSize = 0;

	if (job->useCombiner)
		recSize = job->combineOutAvRecordSize;
	else
		recSize = job->mapOutAvRecordSize;

	int64_t lastSize = recNum * recSize;
	XBT_INFO("before write ch ");
	Chunk* lastCh = hddM->writeCh(lastSize);
	XBT_INFO("after write ch ");
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

	for (int i = fIndex; i <= lIndex; i++) {


		if (!v->at(i)->isInMem) {//if in memory do not read it
			v->at(i)->ch->clinetMB=Mailbox::by_name(taskName);
			hddM->readCh(v->at(i)->ch);
			hddM->deleteCh(v->at(i)->ch);

		}

		//v->erase(v->begin() + i);

		recNum += v->at(i)->records;
	}
	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS,recNum);

	for (int i = fIndex; i <= lIndex; i++) {
		v->erase(v->begin());
	}
	int64_t recSize = 0;

	if (job->useCombiner)
		recSize = job->combineOutAvRecordSize;
	else
		recSize = job->mapOutAvRecordSize;



	int64_t lastSize = recNum * recSize;
	XBT_INFO("beforrrrrrr write ch");
	Chunk* lastCh = hddM->writeCh(lastSize);
XBT_INFO("after ****************write ch");
	spill* lastSpill = new spill();
	lastSpill->ch = lastCh;
	lastSpill->records = recNum;

	v->push_back(lastSpill);

}
