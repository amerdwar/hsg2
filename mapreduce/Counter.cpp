/*
 * Counter.cpp
 *
 *  Created on: Apr 15, 2019
 *      Author: alpha
 */

#include "Counter.h"

Counter::Counter() {


}
int64_t Counter::getCtr(ctr_t t){
	//TODO test if t is exist in map
	return ctrMap.at(t);
}
void Counter::addToCtr(ctr_t t,int64_t c){
if(ctrMap.find(t)==ctrMap.end()){
ctrMap.insert(std::pair<ctr_t,int64_t>(t,c));
}
else{

	ctrMap.at(t)+=c;
}

}
void Counter::setCtr(ctr_t t,int64_t c){
	if(ctrMap.find(t)==ctrMap.end()){
	ctrMap.insert(std::pair<ctr_t,int64_t>(t,c));
	}
	else{

		ctrMap.at(t)=c;
	}

}


Counter::~Counter() {
	// TODO Auto-generated destructor stub
}

