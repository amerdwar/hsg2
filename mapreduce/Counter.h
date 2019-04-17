/*
 * Counter.h
 *
 *  Created on: Apr 15, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_COUNTER_H_
#define MAPREDUCE_COUNTER_H_
#include <map>
#include "../commons/Types.h"
#include <atomic>
class Counter {
public:

	Counter();
	int64_t getCtr(ctr_t t);
    void addToCtr(ctr_t t,int64_t);
	void setCtr(ctr_t t,int64_t);
	virtual ~Counter();
private:
	map<ctr_t,std::atomic<int64_t>> ctrMap;
};

#endif /* MAPREDUCE_COUNTER_H_ */
