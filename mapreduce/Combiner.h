/*
 * Combiner.h
 *
 *  Created on: Mar 11, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_COMBINER_H_
#define MAPREDUCE_COMBINER_H_
#include  "../commons/Types.h"
#include <math.h>
class Combiner {
public:
	int groups;
	double ioSortFactor = 10; //numb of spill to be merge in single step
	double ioSortMb = 100.0; //size of map buffer in mb
	double ioSortSpillPercent = 0.8; //the threshold to trigger spilling
	int mapCombineMinspills = 3; //if the

	double combineCost;

	vector<spill*>* combine(vector<spill*>* v);
	int getNumCombinedRecordes(int groups, int recordes);
	Combiner();
	virtual ~Combiner();
};

#endif /* MAPREDUCE_COMBINER_H_ */
