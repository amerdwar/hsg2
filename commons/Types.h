//sender _rescevier_operatoin
//
enum msg_type {
	cl_nn_wr_file = 1, //client nameNode write file;
	nn_cl_file_ch, //nameNode client file chunks
	cl_dn_wr_ch,
	cl_nn_re_file,
	nn_cl_re_file,
	cl_dn_re_ch, //client send read chunk to data node
	dn_ack_wr_ch,
	cl_nn_ack_ch,
	any,
	hdd,
	hdd_added,
	hdd_check,
hdd_ack,
	end_of_simulation
};

enum hdd_Access{
	hdd_read=1,
	hdd_write

};
