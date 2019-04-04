/*
 * Hdd.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: alpha
 */

#include "Hdd.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(hdd, "Messages specific for this example");
Hdd::Hdd(std::vector<std::string> args) {

	string actorName = this_actor::get_host()->get_name() + "_" + storageName;

	mailbox = Mailbox::by_name(actorName);
	mailbox->set_receiver(Actor::self());

}
Hdd::Hdd(std::string argv) {
	storageName = argv;
//the actor name is host_storagename and this is the mailbox name
	string actorName = this_actor::get_host()->get_name() + "_" + storageName;

	mailbox = Mailbox::by_name(actorName);


	double oneMB = 1024 * 1024;
	double w1 = Engine::get_clock();
	Storage::by_name(argv)->write(oneMB);
	double w2 = Engine::get_clock();
	writeSpeed = oneMB / (w2 - w1);
	//XBT_INFO("write speed is %f ", writeSpeed);

	double r1 = Engine::get_clock();
	Storage::by_name(argv)->write(oneMB);
	double r2 = Engine::get_clock();
	readSpeed = oneMB / (r2 - r1);
	delta = 0.087 * writeSpeed;
	readAccessSize = readAccess * readSpeed; //the speed is in byte per second and the read access time in seconds
	writeAccessSize = writeAccess * writeSpeed; //the speed is in byte per second and the read access time in seconds
////XBT_INFO(" r %f w %f",readAccessSize,writeAccessSize);

}

void Hdd::operator()() {
	mailbox->set_receiver(Actor::self());
	Message * m = nullptr;

	msg_type ty = msg_type::any;

	do {
		void *t;

		m = static_cast<Message*>(mailbox->get());
ty=m->type;
//m=static_cast<Message*> (mailbox->get());

		switch (m->type) {

		case msg_type::end_of_simulation: {
			//XBT_INFO("hdd end simulation ");

			break;
		}
		case msg_type::hdd: { //new write message so scheduale the process
			numWrite++;
			//XBT_INFO(" in hdd %s", m->toString().c_str());
			m->type = msg_type::hdd_added;
			m->generator = m->sender;
			m->sender = m->receiver = mailbox->get_name();
			mailbox->put(m, 0);
			break;
		}

		case msg_type::hdd_added: {
			//XBT_INFO("in added");
			Chunk * ch = static_cast<Chunk*>(m->payload);
			if (isIdle) {
				//XBT_INFO("is idle %i",ch->size);
				isIdle = false;
				if (ch->size > 0) {

					double slice = this->decTimesAndGet(ch->size);

					ch->size = ch->size - slice;
					if (m->returnTag == hdd_Access::hdd_read) {
						//XBT_INFO("before read");
						Storage::by_name(storageName)->read(
								slice + readAccessSize);

						//XBT_INFO("in read access");	////XBT_INFO("read slice ");
					} else {
						double a = Engine::get_clock();
						Storage::by_name(storageName)->write(
								slice + writeAccessSize);
						double b = Engine::get_clock();

					}

					m->type = hdd_check;
					m->payload = ch;

					mailbox->put(m, 0);

				}

			} else {

				m->type = hdd_check;
				//m->trace(" add to jobs after arrive");
				jobs.push(m);
			}

			break;
		}
		case msg_type::hdd_check: {
			//XBT_INFO("in checked");
			Chunk * ch = static_cast<Chunk*>(m->payload);
			if (ch->size == 0) { //the job is complete
				numcompleteWrite++;
				//XBT_INFO(
					//	"the job complete send it pack ,all req is %i, complete is %i",
						//numWrite, numcompleteWrite);
				m->trace(" finish ");
					//XBT_INFO(m->traceStr.c_str());
				if (m->returnTag == hdd_Access::hdd_read) {
					m->type = msg_type::hdd_read_ack;
					//XBT_INFO("read ack");
				} else {
					m->type = msg_type::hdd_write_ack;
					//XBT_INFO("write ack");
				}

				m->sender = mailbox->get_name();
				m->receiver = m->generator;

				XBT_INFO("from hdd %s",m->generator.c_str());
				Mailbox::by_name(m->generator)->put(m, 0); //send the message pack to client
				XBT_INFO("from hdd2");
				if (!jobs.empty()) {
					////XBT_INFO("pop new job ");
					Message *msg = (Message *) jobs.front();
					jobs.pop();
					Chunk * payload = static_cast<Chunk*>(msg->payload);

					double slice1 = this->decTimesAndGet(payload->size);
					payload->size = payload->size - slice1;
					if (slice1 > 0) {
						////XBT_INFO("the slice %f is and ch is %f sender %s",
						//		slice1, *payload, msg->sender.c_str());
						if (m->returnTag == hdd_Access::hdd_read) {
							Storage::by_name(storageName)->read(
									slice1 + readAccessSize);

						} else {
							Storage::by_name(storageName)->write(
									slice1 + writeAccessSize);

						}
					}
					msg->payload = payload;
					msg->trace("exe slice ");
					mailbox->put(msg, 0);

				} else {
					////XBT_INFO("the hdd is idle");
					this->isIdle = true;

				}

			} else { //pop the Q if not empty else go idle
				//////XBT_INFO("jobs eqUAL");
				if (jobs.size() > 0) {
					m->trace(" push to que");
					jobs.push(m);
					Message *msg = (Message *) jobs.front();
					msg->trace(" pop the q");
					jobs.pop();
					Chunk * payload = static_cast<Chunk*>(msg->payload);
					double slice1 = this->decTimesAndGet(payload->size);
					payload->size = payload->size - slice1;
					//double* newSize = *size - slice1;
					//////XBT_INFO("the slice %f is and size is %f sender %s", slice1, *payload,msg->sender.c_str());
					if (m->returnTag == hdd_Access::hdd_read) {
						Storage::by_name(storageName)->read(
								slice1 + readAccessSize);

					} else {
						Storage::by_name(storageName)->write(
								slice1 + writeAccessSize);

					}

					msg->payload = payload;
					msg->trace(" exe slice");
					mailbox->put(msg, 0);
				} else { //there is no other jobs decremnt delta without delay

					double slice1 = this->decTimesAndGet(ch->size);
					ch->size = ch->size - slice1;
					if (m->returnTag == hdd_Access::hdd_read) {
						Storage::by_name(storageName)->read(slice1);

					} else {
						Storage::by_name(storageName)->write(slice1);

					}
					m->payload = ch;
					m->trace(" exe slice without accesstime");
					mailbox->put(m, 0);
				}

			}

			break;
		}
		}
	} while (ty != msg_type::end_of_simulation);
//XBT_INFO("after while");
}
double Hdd::decTimesAndGet(double size) {

	if (size >= delta) {
		size -= delta;

		return delta;
	} else {
		double last = size;
		size = 0;
		return last;
	}
}

Hdd::~Hdd() {
	// TODO Auto-generated destructor stub
}

