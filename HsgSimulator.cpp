/*
 * HsgSimulator.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: alpha
 */

#include "HsgSimulator.h"

HsgSimulator::HsgSimulator() {
	// TODO Auto-generated constructor stub

}

HsgSimulator::~HsgSimulator() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char* argv[])
{
  simgrid::s4u::Engine e(&argc, argv);
  xbt_assert(argc > 2, "Usage: %s platform_file deployment_file\n", argv[0]);

  /* Register the classes representing the actors */

  e.register_actor<NameNode>("master");

  /* Load the platform description and then deploy the application */
  e.load_platform(argv[1]);
  e.load_deployment(argv[2]);

  /* Run the simulation */
  e.run();

  XBT_INFO("Simulation is over");

  return 0;
}
