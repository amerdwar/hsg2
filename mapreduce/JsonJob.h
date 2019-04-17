/*
 * JsonJob.h
 *
 *  Created on: Apr 16, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_JSONJOB_H_
#define MAPREDUCE_JSONJOB_H_
#include "JobInfo.h"

#include "../json/json/json.h"
#include <fstream>
class JsonJob {
public:
	JsonJob();
	JobInfo* getJobFromJson(string file);
	virtual ~JsonJob();
};

#endif /* MAPREDUCE_JSONJOB_H_ */
