/*
 * YarnSchedulerBase.cpp
 *
 *  Created on: Dec 12, 2020
 *      Author: amer
 */

#include "YarnSchedulerBase.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(baseScheduler,
		"Messages specific for this example");
sch_type YarnSchedulerBase::type ;

YarnSchedulerBase::YarnSchedulerBase() {
	// TODO Auto-generated constructor stub

}

void YarnSchedulerBase::updateStat() {
	double timeSinceLastE = 0.0;
	double simTime=Engine::get_clock() ;
	timeSinceLastE = simTime- timeLastEvent; //here we calculate the time slide

	if (timeSinceLastE==0 && timeLastEvent!=0){
		testStr+=to_string(simTime)+"("+to_string(timeLastEvent)+")("+to_string(freeContainers )+")"+"\n";
	}
	timeLastEvent =simTime;

	areaNumInQ += this->numInQ * timeSinceLastE;
	double serverStatusStep
			= (((numContainers - freeContainers) * timeSinceLastE)
					/ numContainers);

	areaServerStatus += serverStatusStep;
//	testStr+=to_string(serverStatusStep)+"("+to_string(freeContainers)+")("+to_string(timeSinceLastE)+")"+"\n";
}


void YarnSchedulerBase::exportStat() {
	this->updateStat();

endTime=Engine::get_clock();
double simTime=endTime-this->startTime;
	ofstream myfile;
	auto jTime = std::chrono::system_clock::now();
	std::time_t jjt = std::chrono::system_clock::to_time_t(jTime);

	myfile.open(
			"resources/results/q/" +this-> qName + " " + std::ctime(&jjt) + ".html");
	string s = "<html><head></head><body><table><th>Statistic name</th><th>Value</value>";
	s+="<tr><td>Average delay</td><td>"+to_string( this->totalDelays/this->numDelayedJobs)+"</td></tr>";
	s+="<tr><td>Average Q length</td><td>"+to_string( this->areaNumInQ/simTime)+"</td></tr>";
	s+="<tr><td>Q  utilization</td><td>"+to_string(this->areaServerStatus/simTime)+"</td></tr>";
	s+="</table>"+testStr+"</body><html>";

	myfile << s;
	myfile.close();

}
YarnSchedulerBase::~YarnSchedulerBase() {
	// TODO Auto-generated destructor stub
}

