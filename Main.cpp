/*
 * Main.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: alpha
 */

#include <simgrid/s4u.hpp>
#include "hdfs/NameNode.h"
#include "hdfs/DataNode.h"
#include "hdfs/Client.h"
#include "yarn/ResourceManager.h"
#include "yarn/NodeManager.h"
#include "mapreduce/MRClient.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Main, "Messages specific for this example");
int main(int argc, char* argv[]) {
	simgrid::s4u::Engine e(&argc, argv);
	xbt_assert(argc > 2, "Usage: %s platform_file deployment_file\n", argv[0]);

	/* Register the classes representing the actors */

	e.register_actor<NameNode>("nameNode");
	e.register_actor<Client>("client");
	e.register_actor<DataNode>("dataNode");
	e.register_actor<ResourceManager>("ResourceManager");
	e.register_actor<MRClient>("mrclient");
	e.register_actor<NodeManager>("nodeManager");

	/* Load the platform description and then deploy the application */
	e.load_platform(argv[1]);
	e.load_deployment(argv[2]);

	//simgrid::s4u::Actor::create("client", simgrid::s4u::Host::by_name("host1"), Client("host2_nameNode"));

	/* Run the simulation */
	e.run();
	XBT_INFO("**************END OF SIMULATION  ****************");

	return 0;
}
