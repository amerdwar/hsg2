/*
 * Counter.cpp
 *
 *  Created on: Apr 15, 2019
 *      Author: alpha
 */

#include "Counter.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Counter, "Messages specific for this example");
Counter::Counter(string jName,string Qname) {
this->jName=jName;
this->Qname=Qname;

}
double Counter::getCtr(ctr_t t){

	if(ctrMap.find(t)==ctrMap.end()){
		//XBT_INFO("error no such element");
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

//XBT_INFO("error subtract from null in map");
exit(0);

	}
	else{

		ctrMap.at(t)-=c;
	}
mtx.unlock();
}



void Counter::printCtrs(){
	mtx.lock();
	ofstream myfile;
	 auto jTime = std::chrono::system_clock::now();
	  std::time_t jjt = std::chrono::system_clock::to_time_t(jTime);

myfile.open("resources/results/"+jName+" "+std::ctime(&jjt)+".html");
string s="\n";
s+="<html><title>"+jName+"</title>";


s+="<body><table border=1>";

s+="<tr><td>job name</td><td>"+jName+"</td></tr>";
for (auto const&t : ctrMap){

	s+="<tr>";
s+="<td>"+ctr_t_str[t.first]+"</td><td> "+to_string(t.second)+"</td>";
s+="</tr>";
}
s+="<tr><td>Qname</td><td>"+this->Qname+"</td></tr>";
s+="</table></body></html>";
myfile<<s;
myfile.close();
mtx.unlock();
}

Counter::~Counter() {
	// TODO Auto-generated destructor stub
}

