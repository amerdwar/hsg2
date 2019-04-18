/*
 * Counter.h
 *
 *  Created on: Apr 15, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_COUNTER_H_
#define MAPREDUCE_COUNTER_H_


#include <atomic>
#include "../commons/CtrType.h"
#include <map>
using namespace std;
class Counter {
public:

	Counter();
	int64_t getCtr(ctr_t t);
    void addToCtr(ctr_t t,int64_t);
	void setCtr(ctr_t t,int64_t);
	virtual ~Counter();
private:

	map<ctr_t,atomic<int64_t>> ctrMap;

};

#endif /* MAPREDUCE_COUNTER_H_ */
