/*
 * CtrType.h
 *
 *  Created on: Apr 18, 2019
 *      Author: alpha
 */

#ifndef COMMONS_CTRTYPE_H_
#define COMMONS_CTRTYPE_H_
#include <vector>
#include <string>
using namespace std;
 enum  ctr_t {
	 MAP_INPUT_RECORDS,
	MAP_OUTPUT_RECORDS,
	MAP_SKIPPED_RECORDS,
	MAP_INPUT_SIZE,
	MAP_OUTPUT_SIZE,
	COMBINE_INPUT_RECORDS,
	COMBINE_OUTPUT_RECORDS,
	COMBINE_INPUT_SIZE,
	COMBINE_OUTPUT_SIZE,
	COMBINE_INPUT_GROUPS,
	COMBINE_OUTPUT_GROUPS,
	REDUCE_INPUT_GROUPS,
	REDUCE_INPUT_RECORDS,
	REDUCE_OUTPUT_RECORDS,
	REDUCE_SKIPPED_GROUPS,
	REDUCE_SKIPPED_RECORDS,
	SPILLED_RECORDS,
	START_TIME,
	STOP_TIME,
	REDUCE_SHUFFLE_BYTES,
	FILE_BYTES_READ,
	FILE_BYTES_WRITTEN,
	HDFS_BYTES_READ,
	HDFS_BYTES_WRITTEN,
	HDD_READ,
	HDD_WRITE,
	CPU_WORK,
	NET_IN,
	NET_OUT,
	test,
	FILE_BYTES_READ_TEST,
	FILE_BYTES_WRITTEN_TEST,
	MAP_OUTPUT_BYTES,
	JOB_START_TIME,
	JOB_STOP_TIME,
	JOB_TOTAL_TIME,
	DURATION,
	SHUFFLE,
	process_time,
	avMappersTime,
	avReducersTime,
	Data_local_map_tasks,
	map_spilled_recordes,
	reduce_spilled_recordes,
	map_file_bytes_read,
	map_file_bytes_write,
	reduce_file_bytes_read,
	reduce_file_bytes_write,
	memory
 };

#endif /* COMMONS_CTRTYPE_H_ */
