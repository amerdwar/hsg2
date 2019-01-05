/*
 * HsgSimulator.h
 *
 *  Created on: Dec 29, 2018
 *      Author: alpha
 */

#ifndef HSGSIMULATOR_H_
#define HSGSIMULATOR_H_
#include <simgrid/s4u.hpp>
#include "distributions/RandClass.h"
#include "hdfs/NameNode.h"
#include <iostream>
#include <string>
using namespace std;
XBT_LOG_NEW_DEFAULT_CATEGORY(s4u_app_masterworker, "Messages specific for this example");
class HsgSimulator {
public:
	HsgSimulator();
	virtual ~HsgSimulator();
};

#endif /* HSGSIMULATOR_H_ */
