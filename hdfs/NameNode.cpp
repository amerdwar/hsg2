/*
 * NameNode.cpp
 *
 *  Created on: Dec 27, 2018
 *      Author: alpha
 */

#include "NameNode.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(hsg2, "Messages specific for this example");
//16777216
//134217728
//67108864
//100663296
int64_t NameNode::chunkSize = 134217728;

NameNode::NameNode(std::vector<std::string> args) {


	nameNodeName = args[1];
//mailbox=Mailbox::by_name(this_actor::get_host()->get_name()+nameNodeName);
	if (args.size() > 1)
		NameNode::chunkSize = std::stoi(args[2]) * 1024 * 1024;
	Engine* e = simgrid::s4u::Engine::get_instance();

	mailbox = Mailbox::by_name(nameNodeName);
	mailbox->set_receiver(Actor::self());

	racks = e->get_filtered_netzones<simgrid::kernel::routing::ClusterZone>();

	replicatinNum = 3;
	allDires = new map<string, DirFiles *>();
	dataNodes = new map<MailboxPtr, vector<Chunk*>>;

}

void NameNode::operator()() { //the simulation loop

	Message * m = nullptr;
	do {

		m = static_cast<Message*>(mailbox->get());
		switch (m->type) {

		case msg_type::end_of_simulation: {
			XBT_INFO("end name node");
			for (auto a = dataNodes->begin(); a != dataNodes->end(); a++) {
				a->first->put(m, 1522);
				XBT_INFO("end name node   send to node %s",a->first->get_name().c_str());
			}
			XBT_INFO("end name node");
			break;
		}
		case msg_type::cl_nn_wr_file: {
			HdfsFile * f = static_cast<HdfsFile*>(m->payload);

			hdfs_write(f->dir, f->name, f->size, Mailbox::by_name(m->sender));

			break;
		}

		case msg_type::cl_nn_ack_ch: {
			XBT_INFO("ack from client");
			HdfsFile * f = static_cast<HdfsFile*>(m->payload);
			allDires->at(f->dir)->Files->at(f->name)->isAck = true;
			break;
		}
		case msg_type::cl_nn_re_file: {
			XBT_INFO("in read");
			HdfsFile * f = static_cast<HdfsFile*>(m->payload);
			Message *msg = new Message(msg_type::nn_cl_re_file, nameNodeName,
					m->sender, 0, allDires->at(f->dir)->Files->at(f->name));

			Mailbox::by_name(m->sender)->put(msg, 1024);

			break;
		}
		case msg_type::cl_nn_re_dir: {
					XBT_INFO("in read dir");
					string * dd = static_cast<string*>(m->payload);
					Message *msg = new Message(msg_type::nn_cl_re_dir, nameNodeName,
							m->sender, 0, allDires->at(*dd));

					Mailbox::by_name(m->sender)->put(msg, 1024);

					break;
				}
		}

	} while (m->type != msg_type::end_of_simulation);

}

bool NameNode::hdfs_write(string dir, string file, int64_t file_size,
		simgrid::s4u::MailboxPtr sender) {

//choose the datanode for the chnuk
	//send the chnk for the first no
	xbt_assert(replicatinNum > 0, "replication num is 0");

	HdfsFile* f = new HdfsFile(dir, file, file_size);

	if (allDires->find(dir) == allDires->end()) {	//add dir if not exist
		DirFiles* d = new DirFiles(dir);

		allDires->insert(std::pair<string, DirFiles*>(dir, d));

	}
	long int rackNums = racks.size();

	xbt_assert(rackNums > 0, "num of rack is 0");
	int64_t numCh = file_size / chunkSize;

	if (file_size % chunkSize != 0) {

		numCh++;
	}

	for (int chindex = 0; chindex < numCh; chindex++) {

		vector<simgrid::s4u::MailboxPtr>* hosts_to_write = new vector<
				simgrid::s4u::MailboxPtr>();

		//select random rack
		int64_t rackId = RandClass::getRand(0, rackNums - 1);

		//first we have to write the chunk the random host in the selected rack
		auto selectedRack = racks.at(rackId);
		xbt_assert(selectedRack->get_all_hosts().size() > 0,
				"num of host in rack %d is 0", rackId);
		simgrid::s4u::MailboxPtr h1 = simgrid::s4u::Mailbox::by_name(
				this->randomHostInRack(selectedRack)->get_name() + "_dataNode");

		hosts_to_write->push_back(h1);
		simgrid::s4u::MailboxPtr h2 = nullptr;
		if (replicatinNum > 1) {//choose another host in another rack if exist
			if (racks.size() > 1) {
				//choose random rack !=rackid
				int64_t temId = 0;
				do {
					temId = RandClass::getRand(0, rackNums - 1);
				} while (rackId == temId);
				//chose rand host != h1
				xbt_assert(racks.at(temId)->get_all_hosts().size() > 0,
						"num of host is 0");

				if (racks.at(temId)->get_all_hosts().size() > 1) {
					h2 = simgrid::s4u::Mailbox::by_name(
							this->randomHostInRack(racks.at(temId))->get_name()
									+ "_dataNode");
				} else {	//there is one host host
					h2 = simgrid::s4u::Mailbox::by_name(
							racks.at(temId)->get_all_hosts().at(0)->get_name()
									+ "_dataNode");
				}

			} else {	//racks size is 1
				xbt_assert(racks.at(0)->get_all_hosts().size() > 0,
						"num of host is 0");
				if (racks.at(0)->get_all_hosts().size() > 1) {
					h2 = simgrid::s4u::Mailbox::by_name(
							this->randomHostInRackExceptHost(racks.at(0),
									h1->get_name())->get_name() + "_dataNode");
				} else {

					h2 = simgrid::s4u::Mailbox::by_name(
							racks.at(0)->get_all_hosts().at(0)->get_name()
									+ "_dataNode");
				}

			}

			hosts_to_write->push_back(h2);
		}
		simgrid::s4u::MailboxPtr h3 = nullptr;
		if (replicatinNum > 2) {	//third replication is in the same rack

			if (racks.at(rackId)->get_all_hosts().size() > 2) {
				std::vector<string> s;
				s.push_back(h1->get_name());
				s.push_back(h2->get_name());
				h3 = simgrid::s4u::Mailbox::by_name(
						this->randHostExcept(selectedRack, s)->get_name()
								+ "_dataNode");
			} else {

				h3 = simgrid::s4u::Mailbox::by_name(
						selectedRack->get_all_hosts().at(0)->get_name()
								+ "_dataNode");
			}

			hosts_to_write->push_back(h3);
		}
		if (replicatinNum > 3) {
			for (int i = 4; i <= replicatinNum; i++) {

				int64_t rackId1 = RandClass::getRand(0, rackNums - 1);
				//first we have to write the chunk the random host in the selected rack
				auto selectedRack1 = racks.at(rackId1);
				xbt_assert(selectedRack1->get_all_hosts().size() > 0,
						"num host is 0 in rack num %i", rackId1);

				simgrid::s4u::MailboxPtr tempHost =
						simgrid::s4u::Mailbox::by_name(
								this->randomHostInRack(selectedRack1)->get_name()
										+ "_dataNode");
				hosts_to_write->push_back(tempHost);
			}

		}
//now we have vector of hosts to write the chunk on it
		Chunk *ch = new Chunk(dir, f->name, f->id, chunkSize);
		if (file_size % chunkSize != 0) {
			if (chindex == (numCh - 1)) {
				//if the chunk is the last chunk its size with pe the reminderof filesize/chunkSize
				ch->size = f->size % chunkSize;
			}
		}
		ch->clinetMB = sender;
		ch->nodes = hosts_to_write;
		f->chunks->push_back(ch);
		for (int i = 0; i < hosts_to_write->size(); i++) {
			if (dataNodes->find(hosts_to_write->at(i)) == dataNodes->end()) {
				vector<Chunk*> dnChunks;
				dnChunks.push_back(ch);
				dataNodes->insert(
						std::pair<MailboxPtr, vector<Chunk*>>(
								hosts_to_write->at(i), dnChunks));
			} else {
				dataNodes->at(hosts_to_write->at(i)).push_back(ch);
			}

		}

	}

	auto ret = allDires->at(dir)->Files->insert(
			std::pair<string, HdfsFile *>(file, f));
	if (ret.second == false) {
		XBT_INFO("file exist");
		return 0;

	}
//send back to sender with the list of data nodes

	Message *msg = new Message(msg_type::nn_cl_file_ch, nameNodeName,
			sender->get_name(), 0, allDires->at(dir)->Files->at(file));

	sender->put(msg, 1522);

	return true;
}
NameNode::~NameNode() {
	// TODO Auto-generated destructor stub
}

simgrid::s4u::Host* NameNode::randomHostInRack(
		simgrid::kernel::routing::ClusterZone* rack) {
	auto hosts = rack->get_all_hosts();

	return hosts.at(RandClass::getRand(0, hosts.size() - 1));

}

simgrid::s4u::Host* NameNode::randomHostInRackExceptHost(
		simgrid::kernel::routing::ClusterZone* rack, string host) {
	auto hosts = rack->get_all_hosts();
	simgrid::s4u::Host* h;
	if (hosts.size() > 1) {	//if we have more than one host return any random host in the rack except the host whose name is param host
		do {
			h = hosts.at(RandClass::getRand(0, hosts.size() - 1));

		} while (h->get_name().compare(host) == 0);
		return h;
	} else {	//there is one host in the rack

		return hosts.at(0);
	}
}
simgrid::s4u::Host* NameNode::randHostExcept(
		simgrid::kernel::routing::ClusterZone* rack, std::vector<string> exc) {
	auto hosts = rack->get_all_hosts();
	simgrid::s4u::Host* h;
	if (hosts.size() > 1) {	//if we have more than one host return any random host in the rack except the host whose name is param host
		bool reScan = false;
		do {
			h = hosts.at(RandClass::getRand(0, hosts.size() - 1));
			reScan = false;
			for (auto ex : exc) {
				if (ex.compare(h->get_name() + "_dataNode") == 0) {
					reScan = true;
					XBT_INFO(" equal %s ,%s", ex.c_str(),
							h->get_name().c_str());
				} else {
					XBT_INFO(" not equal %s ,%s", ex.c_str(),
							h->get_name().c_str());

				}
			}

		} while (reScan);

		return h;
	} else {	//there is one host in the rack

		return hosts.at(0);
	}

}
