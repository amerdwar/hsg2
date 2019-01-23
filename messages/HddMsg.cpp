/*
 * HddMsg.cpp
 *
 *  Created on: Jan 20, 2019
 *      Author: alpha
 */

#include "HddMsg.h"

HddMsg::HddMsg(double totalTime,double deltaTime){

	// TODO Auto-generated constructor stub

}

HddMsg::~HddMsg() {
	// TODO Auto-generated destructor stub
}

bool HddMsg::hasNext(){
    return this->totalTime>0;
}
double HddMsg::decTimesAndGet(){
    times++;

    if(totalTime >= deltaTime){
                totalTime -= deltaTime;


                return deltaTime;
            }else{
                double last=totalTime;
                totalTime=0;
                return last;
            }
}
