//sender _rescevier_operatoin
//
#include <string.h>
#include "../hdfs/DirFiles.h"
using namespace std;
enum msg_type {
	cl_nn_wr_file = 1, //client nameNode write file;
	nn_cl_file_ch, //nameNode client file chunks
	cl_dn_wr_ch,
	cl_nn_re_file,
	nn_cl_re_file,
	cl_dn_re_ch,
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
	end_of_simulation
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
	DirFiles dir;

	int reducersNum = 1; //these for reducer
	int64_t fIndex = 0; //need for map
	int64_t chIndex = 0; //need for map

};

struct allocateRes {
	allocate_type type;
	string requester;
	string nodeManager;
	DirFiles dir;
	int64_t fIndex = 0;
	int64_t chIndex = 0;
};
