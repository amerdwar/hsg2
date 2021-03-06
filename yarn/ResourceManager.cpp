/*
 * ResourceManager.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: alpha
 */

#include "ResourceManager.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(ResourceManager,
		"Messages specific for this example");
int ResourceManager::numCorePerContainer = 1; //to specify the containers number on each host
ResourceManager::ResourceManager(std::vector<std::string> args) {
	xbt_assert(args.size() > 0, "the arguments must be more than one");
	this->nameNodeName = args[1];
	this->thisName = this_actor::get_host()->get_name() + "_"
			+ this_actor::get_name();
	nnmb = simgrid::s4u::Mailbox::by_name(nameNodeName);
	thismb = Mailbox::by_name(thisName);
	thismb->set_receiver(Actor::self());

	initNodeManagers();
	numFreeContainers = numAllContainers; //on create all the containers are free
	scheduler = this->getScheduler(numAllContainers, containers);
	XBT_INFO("in resourse man");
//run heart beater
	heartBeater = this_actor::get_host()->get_name() + "_heartBeater";
	ActorPtr beater = Actor::create(heartBeater, this_actor::get_host(),
			HeartBeater(thismb->get_name(), heartBeater));

}
YarnSchedulerBase* ResourceManager::getScheduler(int numAllContainers,
		std::map<string, int> containers) {
	switch (YarnSchedulerBase::type) {
	case sch_type::fifo: {
		return new FIFOScheduler(numAllContainers, containers);
		break;
	}
	case sch_type::fair: {
		return new FairScheduler(numAllContainers, containers);
		break;
	}
	case sch_type::capacity: {
		return new CapacityScheduler(numAllContainers, containers);
		break;
	}
	default: {
		return new FIFOScheduler(numAllContainers, containers);
		break;
	}

	}

}
void ResourceManager::operator()() {

	Message *m = nullptr;
	do {
		//sleep and send heart beat to parent

		m = static_cast<Message*>(thismb->get());
		 this_actor::execute(50000);
		switch (m->type) {
		case msg_type::end_of_simulation: {
			////XBT_INFO("resource manager end of simulation end simulation ");
			//send this message to heart beater
			Mailbox::by_name(heartBeater)->put(m, 0);
			for (auto a : containers) {
				string nodm = a.first + "_nodeManager";
				Message *m = new Message(msg_type::end_of_simulation, thisName,
						nodm, 1, nullptr);
				Mailbox::by_name(nodm)->put(m, 1522);
			}
			if (YarnSchedulerBase::type==sch_type::capacity){
				CapacityScheduler* cs=static_cast<CapacityScheduler*>(this->scheduler);
				cs->exportQstat();

			}else{
				this->scheduler->exportStat();

			}
			break;
		}
		case msg_type::cl_rm_send_job: {
			////XBT_INFO("receive job name  ");
			JobInfo *j = static_cast<JobInfo*>(m->payload);

			scheduler->addJob(j);

			break;
		}

		case msg_type::heart_beat: {
			//TODO update stat and jobs

			std::vector<allocateRes*> resV = scheduler->allocate();
			for (auto resp : resV) {
				endCounter = 0;

				if (resp->type == allocate_type::app_master_all) {
					Mailbox *nodeManmb = Mailbox::by_name(resp->nodeManager);
					Message *resMSg = new Message(msg_type::allocate_res,
							thismb->get_name(), nodeManmb->get_name(), 0, resp);
					//	////XBT_INFO("allocate on node  %s",
					//nodeManmb->get_name().c_str());
					nodeManmb->put(resMSg, 1522);

				} else {
					Mailbox *reMb = Mailbox::by_name(resp->requester);
					Message *resMSg = new Message(msg_type::allocate_res,
							thismb->get_name(), resp->requester, 0, resp);
					reMb->put(resMSg, 1522);

					scheduler->printRes(resp);
				}

			}

			break;
		}
		case msg_type::free_con: {
			string *str = static_cast<string*>(m->payload);
			scheduler->freeCon(*str);

			break;
		}
		case msg_type::finish_job: {
			JobInfo *jj = static_cast<JobInfo*>(m->payload);
			Message *finishMsg3 = new Message(msg_type::finish_job, thisName,
					jj->user, 0, jj);
			Mailbox::by_name(jj->user)->put(finishMsg3, 1522);
			//send message to client finish job
			scheduler->finishJob(jj);
			break;
		}
		case msg_type::allocate_req: {
			allocateReq *reqall = static_cast<allocateReq*>(m->payload);
			scheduler->addReq(reqall);
			break;
		}

		}

	} while (m->type != msg_type::end_of_simulation);

}

void ResourceManager::initNodeManagers() {

	Engine *e = simgrid::s4u::Engine::get_instance();

	auto racks =
			e->get_filtered_netzones<simgrid::kernel::routing::ClusterZone>();
	for (auto rack : racks) {
		for (auto host : rack->get_all_hosts()) {
			host->set_property("rack", rack->get_name());
			//	////XBT_INFO("pro  %s", host->get_property("rack"));
			int numCon = host->get_core_count() / this->numCorePerContainer; //num containers = num cores per host/num core per container
			numAllContainers += numCon;
			containers.insert(std::pair<string, int>(host->get_name(), numCon));
			//create node manager actor on each host

		} //until here we have map of hosts and how many container they have

	}

}

ResourceManager::~ResourceManager() {
// TODO Auto-generated destructor stub
}

