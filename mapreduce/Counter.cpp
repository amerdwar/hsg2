/*
 * Counter.cpp
 *
 *  Created on: Apr 15, 2019
 *      Author: alpha
 */

#include "Counter.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Counter, "Messages specific for this example");
Counter::Counter(string jName) {
this->jName=jName;

}
double Counter::getCtr(ctr_t t){
	//TODO test if t is exist in map
	if(ctrMap.find(t)==ctrMap.end()){
		XBT_INFO("error no such element");
		exit(0);
	}
	return ctrMap.at(t);
}
void Counter::addToCtr(ctr_t t,double c){
	mtx.lock();
if(ctrMap.find(t)==ctrMap.end()){

ctrMap.insert(std::pair<ctr_t,double>(t,c));
}
else{

	ctrMap.at(t)=ctrMap.at(t)+c;
}
mtx.unlock();

}
void Counter::setCtr(ctr_t t,double c){
	mtx.lock();
	if(ctrMap.find(t)==ctrMap.end()){

	ctrMap.insert(std::pair<ctr_t,double>(t,c));

	}
	else{

		ctrMap.at(t)=c;
	}
mtx.unlock();
}

void Counter::subCtr(ctr_t t,double c){
	mtx.lock();
	if(ctrMap.find(t)==ctrMap.end()){

XBT_INFO("error subtract from null in map");
exit(0);

	}
	else{

		ctrMap.at(t)-=c;
	}
mtx.unlock();
}



void Counter::printCtrs(){
	ofstream myfile;
myfile.open("resources/results/"+jName);
string s="\n";
s+="job name:"+jName+"\n";
for (auto const&t : ctrMap){
s+=ctr_t_str[t.first]+": "+to_string(t.second)+"\n";
}
myfile<<s;
myfile.close();

}

Counter::~Counter() {
	// TODO Auto-generated destructor stub
}

