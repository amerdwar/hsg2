/*
 * Counter.h
 *
 *  Created on: Apr 15, 2019
 *      Author: alpha
 */

#ifndef MAPREDUCE_COUNTER_H_
#define MAPREDUCE_COUNTER_H_


#include <fstream>
#include "../commons/CtrType.h"
#include <map>
#include <simgrid/s4u.hpp>
#include <mutex>          // std::mutex
#include <chrono>
#include <ctime>

using namespace std;
class Counter {
public:
string jName;
	Counter(string jName);

	std::mutex mtx;
	vector<string> ctr_t_str {



		"MAP_INPUT_RECORDS",
		"MAP_OUTPUT_RECORDS",
		"MAP_SKIPPED_RECORDS",
		"MAP_INPUT_SIZE",
		"MAP_OUTPUT_SIZE",
		"COMBINE_INPUT_RECORDS",
		"COMBINE_OUTPUT_RECORDS",
		"COMBINE_INPUT_SIZE",
		"COMBINE_OUTPUT_SIZE",
		"COMBINE_INPUT_GROUPS",
		"COMBINE_OUTPUT_GROUPS",
		"REDUCE_INPUT_GROUPS",//	Reduce_shuffle_bytes,
		"REDUCE_INPUT_RECORDS",
		"REDUCE_OUTPUT_RECORDS",
		"REDUCE_SKIPPED_GROUPS",
		"REDUCE_SKIPPED_RECORDS",
		"SPILLED_RECORDS",
		"START_TIME",
		"STOP_TIME",
		"REDUCE_SHUFFLE_BYTES",
		"FILE_BYTES_READ",
		"FILE_BYTES_WRITTEN",
	"HDFS_BYTES_READ",
		"HDFS_BYTES_WRITTEN",
		"HDD_READ",
		" HDD_WRITE",
		"CPU_WORK",
		"NET_IN",
		"NET_OUT",
		"test",
		"FILE_BYTES_READ_TEST",
		"FILE_BYTES_WRITTEN_TEST",
		"MAP_OUTPUT_BYTES",
		"JOB_START_TIME",
		"JOB_STOP_TIME",
		"JOB_TOTAL_TIME",
		"DURATION",
		"SHUFFLE",
		"process_time",
		"avMappersTime",
		"avReducersTime",
		"Data_local_map_tasks",
		"map_spilled_recordes",
			"reduce_spilled_recordes",
			"map_file_bytes_read",
			"map_file_bytes_write",
			"reduce_file_bytes_read",
			"reduce_file_bytes_write"

	};

	double getCtr(ctr_t t);
    void addToCtr(ctr_t t,double);
	void setCtr(ctr_t t,double);
	void subCtr(ctr_t t,double c);
	void printCtrs();
	virtual ~Counter();
    private:

	map<ctr_t,double> ctrMap;

};

#endif /* MAPREDUCE_COUNTER_H_ */
