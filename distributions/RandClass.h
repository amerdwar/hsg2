/*
 * RandClass.h
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#ifndef DISTRIBUTIONS_RANDCLASS_H_
#define DISTRIBUTIONS_RANDCLASS_H_
#include <random>
#include <time.h>
#include "../distributions/RandClass.h"
class RandClass {
public:
	RandClass();
	static int current_time_nanoseconds();
	virtual ~RandClass();
	static int64_t getRand(int64_t min,int64_t max);
};

#endif /* DISTRIBUTIONS_RANDCLASS_H_ */
