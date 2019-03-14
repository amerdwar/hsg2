/*
 * Combiner.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: alpha
 */

#include "Combiner.h"

Combiner::Combiner() {
	// TODO Auto-generated constructor stub

}
vector<spill*>* Combiner::combine(vector<spill*>* v) {
	vector<spill*>* resV = new vector<spill*>();

	int num = v->size();
	if (num < mapCombineMinspills)
		return v;

	int n = num;
	while (true) {
		int l = n - ioSortFactor;
		if(l==0){
		//TODO merge from 0 to factor;

			return resV;
		}
		else
		if(l<ioSortFactor){
			int t=n-l;
			l=n-t+1;
//TODO mege from 0 to l-1 erase and push one spill

		}else {


		}



	}

//TODO combine spills to one spill and if
	return resV;

}

Combiner::~Combiner() {
	// TODO Auto-generated destructor stub
}

int Combiner::getNumCombinedRecordes(int groups, int rec) {
	double a = 1.0 - 1.0 / groups;
	double n = (double) rec;
	return (1 - pow(a, n)) / (1 - a);

}
