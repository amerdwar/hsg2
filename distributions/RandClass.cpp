/*
 * RandClass.cpp
 *
 *  Created on: Dec 28, 2018
 *      Author: alpha
 */

#include "RandClass.h"

RandClass::RandClass() {
	// TODO Auto-generated constructor stub

}
/**
 * @breif to generate random number between two variables
 * @param #min the random number should be equal or less than min
 * #max the random number should be equal or greator than max
 * @return return random number between min and max
 */
 int64_t RandClass::getRand(int64_t min,int64_t max){
srand((unsigned int)current_time_nanoseconds());
return rand()%(max-min + 1) + min;
}
//@breif return the current time in nano second
 int RandClass::current_time_nanoseconds(){
    struct timespec tm;
    clock_gettime(CLOCK_REALTIME, &tm);
    return tm.tv_nsec;
}
RandClass::~RandClass() {
	// TODO Auto-generated destructor stub
}

