//sender _rescevier_operatoin
//
#include <string.h>
#include "../hdfs/DirFiles.h"
#include "../mapreduce/JobInfo.h"
using namespace std;
enum msg_type {
	cl_nn_wr_file = 1, //client nameNode write file;
	nn_cl_file_ch, //nameNode client file chunks
	cl_dn_wr_ch,
	cl_nn_re_file,
	cl_nn_re_dir,
	nn_cl_re_file,
	nn_cl_re_dir,
	cl_dn_re_ch,
	cl_dn_del_ch,
	dn_cl_re_ack_ch,
	//client send read chunk to data node
	dn_ack_wr_ch,
	cl_nn_ack_ch,
	any,
	hdd,
	hdd_added,
	hdd_check,
	hdd_read_ack,
	hdd_write_ack,
	cl_rm_send_job,
	heart_beat,
	free_con,
	finish_job,
	end_of_simulation,
	allocate_res,
	allocate_req,
	map_finish,
	map_output_req,
	map_output_res,
	reducer_finish,
	app_master_finish,
	finish_copier,
	ack_out_copy,
	cl_dn_del_ch_ack
};

enum hdd_Access {
	hdd_read = 1, hdd_write

};
enum allocate_type {
	map_all, reduce_all, app_master_all
};

struct allocateReq { //the number of mappers equal to num of ch
	allocate_type type;
	string requester; //
	DirFiles* dir;
JobInfo* job;
	int reducersNum = 1; //these for reducer
	int redId=0;
	int64_t fIndex = 0; //need for map
	int64_t chIndex = 0; //need for map

};

struct allocateRes {
	allocate_type type;
	string requester;
	string nodeManager;
	DirFiles* dir;
	JobInfo* job;
	int64_t fIndex = 0;
	int64_t chIndex = 0;

	int reducerId=0;
};

struct spill{
Chunk* ch;
bool isInMem=false;
bool isLast=false;
int records;
string taskName="";
};



 enum ctr_t {

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
//	Reduce_shuffle_bytes,

	REDUCE_INPUT_RECORDS,
	REDUCE_OUTPUT_RECORDS,
	REDUCE_SKIPPED_GROUPS,
	REDUCE_SKIPPED_RECORDS,

	SPILLED_RECORDS,
	START_TIME,STOP_TIME,

	REDUCE_SHUFFLE_BYTES,

	FILE_BYTES_READ,
	FILE_BYTES_WRITTEN,

	HDFS_BYTES_READ,
	HDFS_BYTES_WRITTEN,

	HDD_READ, HDD_WRITE,
	CPU_WORK,
	NET_IN, NET_OUT,

	test, FILE_BYTES_READ_TEST, FILE_BYTES_WRITTEN_TEST,
	MAP_OUTPUT_BYTES, JOB_START_TIME,
	JOB_STOP_TIME, JOB_TOTAL_TIME, DURATION, SHUFFLE, process_time,
	avMappersTime, avReducersTime};
