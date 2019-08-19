/*
 * Combiner.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: alpha
 */

#include "Combiner.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(combiner, "Messages specific for this example");
void Combiner::mergeSpilles(vector<spill*>* v) {

	vector<spill*>* resV = new vector<spill*>();

	int num = v->size();


	if (this->job->useCombiner &&num < mapCombineMinspills){
		return;
	}


	int n = 0;
	while (true) {

		n = v->size();
		int l = n - ioSortFactor;
		if (l <= 0) {
			// merge from 0 to factor; and return one spill in resV

			merge(v, 0, n - 1,true);//true so this is the last merge task => compress spills
			return;
		} else if (l < ioSortFactor) {
			int t = n - l;
			l = n - t + 1;
//TODO mege from 0 to l-1 erase and push one spill
			merge(v, 0, l - 1,false);
		} else {
//TODO merge from 0 to iosortfactor and push one spill
			merge(v, 0, ioSortFactor - 1,false);
		}

	}

}
Combiner::Combiner(JobInfo* job, string dataNode, string taskName) {
	this->job = job;
	this->groups = job->combineGroups;
	this->ioSortFactor = job->ioSortFactor;
	this->ioSortMb = job->ioSortMb;
	this->ioSortSpillPercent = job->ioSortSpillPercent;
	this->dataNode = dataNode;
	this->combineCost = job->combineCost;
this->mapCombineMinspills=job->mapCombineMinspills;
	this->taskName = taskName;
/*
 * f(n)(1+(g-1)/g)
 * */
	this->hddM = new HddMediator(dataNode, taskName, taskName);

}

int64_t Combiner::getNumCombinedRecordes(int64_t q, int64_t n) {
/*	long double a = 1.0 -( 1.0 / qq);
	long double n = (long double) nn;
	return (1 - powl(a, n)) / (1 - a);*/

	//long double a = 1.0 -( 1.0 / qq);
	long double qq=(long double)q;
	long double nn=(long double)n;
	long double a = (qq-1)/qq;
	return (int64_t)( qq-qq* pow(a,nn));

/*
	int64_t	n=(nn*5)/qq;
int64_t q=5;



double s=0;

//C(n,k) * Sum_{j=0..k} (-1)^(k-j) * C(k,j) * j^n.

double a=q;
if(q>n)
	a=n;
	for (double i=1;i<=a;i++){
		double innerSum=0;
	for (double j=1;j<=i;j++){
		innerSum+=pow (-1,i-j)*combination(i,j)*pow(j/q,n);
	}

		double tem =combination(q,i)*innerSum*i;

		s+=tem;


	}
	s/=5;
	s*=qq;
	cout<<endl<<s<<endl;


	return s;
*/

	//int64_t  res=groups*(1-exp(-rec/groups));
//	return res;

}

void Combiner::merge(vector<spill*>* v, int fIndex, int lIndex,bool isLast) {




	int recNum = 0;
	//calculate total read, write, cpu costs
	vector<Chunk*>* vch = new vector<Chunk*>();
	int64_t numRecInMem=0;
	for (int i = fIndex; i <= lIndex; i++) {

		if(!v->at(i)->isInMem)
			vch->push_back(v->at(i)->ch);
		recNum += v->at(i)->records;
	}

	for (int i = fIndex; i <= lIndex; i++) {
		v->erase(v->begin());
	}

	int64_t lastRecNum = this->combine(recNum);
	//int64_t lastRecNum = recNum;
	int64_t recSize = 0;

	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, (double) lastRecNum);
	job->ctr->addToCtr(ctr_t::map_spilled_recordes, (double) lastRecNum);
	double exeF = 0;

	double comp_cost=0;
	if(isLast){
	if(job->useCompression)//so compress here
		comp_cost=(double)lastRecNum*job->compressionCost;
	else
		comp_cost=0;

	}

	if (job->useCombiner) {
		recSize = job->combineOutAvRecordSize;
		//the cost of combine and merge
		exeF =
				(double) (recNum * job->combineCost
						+ lastRecNum * job->mergeCost)+comp_cost;
	} else {
		exeF = (double) (recNum * job->mergeCost)+comp_cost;
		recSize = job->mapOutAvRecordSize;
	}

	int64_t lastSize = lastRecNum * recSize;

	if(isLast&&job->useCompression){
		XBT_INFO("before compress ch %s ",to_string(lastSize).c_str());
		lastSize=(int64_t)(lastSize*job->compressionSize);//compress
	XBT_INFO("after compress ch %s ",to_string(lastSize).c_str());


	}
	Chunk* lastCh = hddM->readChsWrExe(vch, lastSize, exeF);
	XBT_INFO("after write ch ");
	spill* lastSpill = new spill();
	lastSpill->ch = lastCh;
	lastSpill->records = lastRecNum;

	v->push_back(lastSpill);

}
Combiner::~Combiner() {
	// TODO Auto-generated destructor stub
}

int64_t Combiner::combine(int64_t recNum) {
	int64_t combinedRecs = 0;
	if (job->useCombiner) {

		combinedRecs = getNumCombinedRecordes(job->combineGroups, recNum);


		job->ctr->addToCtr(ctr_t::COMBINE_INPUT_RECORDS, (double)recNum );
		job->ctr->addToCtr(ctr_t::COMBINE_OUTPUT_RECORDS, (double)combinedRecs );
		//XBT_INFO("in combiner ,num rec is %i old is %i", combinedRecs,recNum);

	} else {
		combinedRecs = recNum;
		job->ctr->addToCtr(ctr_t::COMBINE_INPUT_RECORDS, 0 );
		job->ctr->addToCtr(ctr_t::COMBINE_OUTPUT_RECORDS, 0 );
		//	XBT_INFO(" in combiner  no co ,num rec is %i", combinedRecs);
	}
	return combinedRecs;

}

void Combiner::mergeReduceSpilles(vector<spill*>* v) {

	vector<spill*>* resV = new vector<spill*>();

	int num = v->size();

	int n = 0;
	while (true) {
		n = v->size();
		int l = n - ioSortFactor;
		if (l <= 0) {
			//TODO merge from 0 to n; and return one spill in resV
			mergeReduce(v, 0, n - 1);
			return;
		} else if (l < ioSortFactor) {
			int t = n - l;
			l = n - t + 1;
//TODO mege from 0 to l-1 erase and push one spill
			mergeReduce(v, 0, l - 1);
		} else {
//TODO merge from 0 to iosortfactor and push one spill
			mergeReduce(v, 0, ioSortFactor - 1);
		}

	}

}

void Combiner::mergeReduce(vector<spill*>* v, int fIndex, int lIndex) {
	int64_t recNum = 0;

	vector<Chunk*>* vch = new vector<Chunk*>();
	for (int i = fIndex; i <= lIndex; i++) {

		if (!v->at(i)->isInMem) { //if in memory do not read it
			v->at(i)->ch->clinetMB = Mailbox::by_name(taskName);
			//hddM->readCh(v->at(i)->ch);
			//hddM->deleteCh(v->at(i)->ch);
			vch->push_back(v->at(i)->ch);
		}

		//v->erase(v->begin() + i);

		recNum += v->at(i)->records;
	}


	for (int i = fIndex; i <= lIndex; i++) {
		v->erase(v->begin());
	}


	//int64_t lastRecNum = this->combine(recNum);
	int64_t lastRecNum = recNum;
	int64_t recSize = 0;

	job->ctr->addToCtr(ctr_t::SPILLED_RECORDS, (double) lastRecNum);
	double exeF = 0;
	/*if (job->useCombiner) {
		recSize = job->combineOutAvRecordSize;
		//the cost of combine and merge
		exeF =
				(double) (recNum * job->combineCost
						+ lastRecNum * job->mergeCost);
	} else {*/
		exeF = (double) (recNum * job->mergeCost);
		recSize = job->mapOutAvRecordSize;
	//}

	int64_t lastSize = lastRecNum * recSize;


	XBT_INFO("beforrrrrrr write ch");
	Chunk* lastCh = hddM->readChsWrExe(vch, lastSize, exeF);
	XBT_INFO("after ****************write ch");
	spill* lastSpill = new spill();
	lastSpill->ch = lastCh;
	lastSpill->records = recNum;

	v->push_back(lastSpill);

}

int64_t Combiner::factory(int64_t a){
	int64_t t=1;
	for (int64_t i=1;i<=a;i++)
		t*=i;
	return t;
}

int64_t Combiner::orders(int64_t n,int64_t q){
	int64_t res=1;
	int64_t t=n;
	for (int64_t i=1;i<=q;i++){
	res*=t;
	t--;
	}
	return res;
}

double Combiner::combination(int64_t n,int64_t q){
	int res;
	if (q==0)
		return 1;
	res=orders(n,q)/factory(q);

	return res;
}
