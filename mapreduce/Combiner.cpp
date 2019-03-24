/*
 * Combiner.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: alpha
 */

#include "Combiner.h"

void Combiner::combine(vector<spill*>* v) {

	vector<spill*>* resV = new vector<spill*>();

	int num = v->size();
	if (num < mapCombineMinspills)
		return ;

	int n = num;
	while (true) {
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
Combiner::Combiner(int groups, double ioSortFacter, double ioSortMb,
		double ioSortSpillPercent, string dataNode, double combineCost,
		spill inMem, string taskName) {
	this->groups = groups;
	this->ioSortFactor = ioSortFacter;
	this->ioSortMb = ioSortMb;
	this->ioSortSpillPercent = ioSortSpillPercent;
	this->dataNode = dataNode;
	this->combineCost = combineCost;
	this->inMem = inMem;
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
	int combinedRecs = getNumCombinedRecordes(groups, recNum);
	this_actor::execute((double) recNum * combineCost);
	int64_t lastSize = combinedRecs * combineOutAvRecordSize;
	Chunk* lastCh = hddM->writeCh(lastSize);

	spill* lastSpill = new spill;
	lastSpill->ch = lastCh;
	lastSpill->records = combinedRecs;
	v->push_back(lastSpill);

}
