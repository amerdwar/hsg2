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



int main(int argc, char* argv[])
{
  simgrid::s4u::Engine e(&argc, argv);
  xbt_assert(argc > 2, "Usage: %s platform_file deployment_file\n", argv[0]);

  /* Register the classes representing the actors */

  e.register_actor<NameNode>("nameNode");
  e.register_actor<Client>("client");
  e.register_actor<DataNode>("dataNode");


  /* Load the platform description and then deploy the application */
  e.load_platform(argv[1]);
  e.load_deployment(argv[2]);


  /* Run the simulation */
  e.run();



  return 0;
}
