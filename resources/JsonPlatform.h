/*
 * JsonPlatform.h
 *
 *  Created on: Apr 30, 2019
 *      Author: alpha
 */

#ifndef RESOURCES_JSONPLATFORM_H_
#define RESOURCES_JSONPLATFORM_H_
#include "../json/json/json.h"
#include <fstream>
#include <string>
#include <boost/format.hpp>
#include "../hdfs/NameNode.h"
#include "../hdfs/Hdd.h"
using namespace std;
class JsonPlatform {
public:
	vector<string> hosts;
	int64_t hid=2;//host id < the host0 is namenode,host1 is resourceManager
	JsonPlatform();
	string hddtype="";
	void creatPlatform(string file);
	string getHostInfo(string router,Json::Value value);
	string getZoneRoutes(vector<string> routers,Json::Value value);
	string get_nn_or_rm(string router, Json::Value value,int h);
	string getDeployJson();
	virtual ~JsonPlatform();
};

#endif /* RESOURCES_JSONPLATFORM_H_ */
