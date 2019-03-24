/*
 * Combiner.h
 *
 *  Created on: Mar 11, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_COMBINER_H_
#define MAPREDUCE_COMBINER_H_
#include  "../commons/Types.h"
#include <simgrid/s4u.hpp>
#include <math.h>
#include "../yarn/HddMediator.h"

using namespace simgrid::s4u;
class Combiner {
public:
	int groups;
	double ioSortFactor = 10; //numb of spill to be merge in single step
	double ioSortMb = 100.0; //size of map buffer in mb
	double ioSortSpillPercent = 0.8; //the threshold to trigger spilling
	int mapCombineMinspills = 3; //if the

	double combineCost=1.0;
    double combineSize=1.0;
    double combineRecords=1.0;
    double combineGroups=1.0;
    double combineOutAvRecordSize=1.0;
    double combineOutAvRecordSize_add=0.0;


	string dataNode;

	HddMediator* hddM;
	string taskName;
	spill* inMem;

void combine(vector<spill*>* v);
	void merge(vector<spill*>* v,int fIndex,int lIndex);
	int getNumCombinedRecordes(int groups, int recordes);
	Combiner(int groups, double ioSortFacter, double ioSortMb,
			double ioSortSpillPercent, string dataNode, double combineCost,
			spill inMem, string taskName);
	virtual ~Combiner();
};

#endif /* MAPREDUCE_COMBINER_H_ */
