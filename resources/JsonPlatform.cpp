/*
 * JsonPlatform.cpp
 *
 *  Created on: Apr 30, 2019
 *      Author: alpha
 */

#include "JsonPlatform.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(jsonPlatform, "Messages specific for this example");
JsonPlatform::JsonPlatform() {
	// TODO Auto-generated constructor stub

}
vector<Capacity*>* JsonPlatform::readCapacityFile(){
	string file="resources/cluster/capacity.json";
	string str;
	vector<Capacity *> *capacityEntrys=new vector<Capacity *> ();
		Json::Value capacityArray;
		std::ifstream jsonFile(file);
		jsonFile >> capacityArray;
		const Json::Value entrys = capacityArray["capacity"];
		int allPercentVals=0;
		for ( int index = 0; index < entrys.size(); ++index ){
		string nameStr=entrys[index]["name"].asString();
		int percentVal=entrys[index]["percent"].asInt();
		allPercentVals+=percentVal;
		if (allPercentVals>100){
			XBT_INFO("capacity.json has bad data sum of percents is greater than 100");
			exit(1);
		}

		Capacity *a=new Capacity(nameStr,percentVal);
		capacityEntrys->push_back(a);
		}
		if (allPercentVals<100){
				XBT_INFO("capacity.json has bad data sum of percents is less than 100");
				exit(1);
			}


	return capacityEntrys;

}
void JsonPlatform::creatPlatform(string file) {

string str;
	Json::Value jobV;
	std::ifstream jsonFile(file);
	jsonFile >> jobV;

	string ss=jobV.toStyledString();

	//XBT_INFO("%s",ss.c_str());

NameNode::chunkSize=jobV["chunkSize"].asInt64()*1024*1024;
NameNode::replicatinNum=jobV["replicatinNum"].asInt();
Hdd::readAccess=jobV["hddreadAccess"].asDouble();
Hdd::writeAccess=jobV["hddwriteAccess"].asDouble();
string schedulerStr=jobV["SchedulerType"].asString();
//XBT_INFO("ss %s",schedulerStr.c_str());
//exit(0);
if (schedulerStr.compare("fair")==0){
	YarnSchedulerBase::type=sch_type::fair;

}else if (schedulerStr.compare("capacity")==0){

	YarnSchedulerBase::type=sch_type::capacity;

}else{
	YarnSchedulerBase::type=sch_type::fifo;
}



Hdd::hddSlice=jobV["hddSlice"].asDouble();

Hdd::hddCpuUseage=jobV["hddCpuUseage"].asDouble();
AppMaster::slowStartNumFinishedMappers=jobV["slowStartNumFinishedMappers"].asDouble();
ResourceManager::numCorePerContainer=jobV["numCorePerContainer"].asInt();


bool gen=jobV["generatePlatformAndDeploy"].asBool();
if(!gen){//do not generate new platform nor deploy
	//XBT_INFO("no generate");

	return;
}


	vector<string> routers;
	boost::format fmt;
	hddtype="single_hdd";
routers.push_back("router0");
	string tem =
			R"(<?xml version='1.0'?>
<!DOCTYPE platform SYSTEM "http://simgrid.gforge.inria.fr/simgrid/simgrid.dtd">
<platform version="4.1">

	<zone id="AS0" routing="Dijkstra">

	<zone id="rack0" routing="Dijkstra">
    <router id="router0" />
	 <storage_type id="%s" size="1024GiB">
	  <model_prop id="Bwrite" value="%s" />
	  <model_prop id="Bread" value="%s" />
	 </storage_type>

)";
	fmt = boost::format(tem) %hddtype
							 %jobV["hddWriteSpeed"].asString()
							 %jobV["hddReadSpeed"].asString()
							 ;
	str+=fmt.str();

str+=get_nn_or_rm("router0",jobV,0);
str+=get_nn_or_rm("router0",jobV,1);
str+=get_route_nn_rm("router0",jobV,0);
str+=get_route_nn_rm("router0",jobV,1);
str+="</zone>";
//Add zones then add hosts to them then connect zones
	//the first rack(i=0) for the rack that contains NameNode and resourceManager
for(int i=1;i<=jobV["racksNum"].asInt();i++){
string stem=R"(	<zone id="%s" routing="Cluster">
			<router id="%s" />)";
string zoneId="rack"+to_string(i);
string routerId="router"+to_string(i);
routers.push_back(routerId);
fmt = boost::format(stem) %zoneId%routerId;
str+=fmt.str();

	for(int j=0;j<jobV["hostsPerRack"].asInt();j++){
str+=getHostInfo(routerId,jobV);
	}
string stem2=R"(<backbone id="%s" bandwidth="%s" latency="%s" />
		</zone>)";
string backb="backbone"+to_string(i);
fmt = boost::format(stem2)%backb
						  %jobV["backBoneLinkSpeed"].asString()
						%jobV["backBoneLinkLatency"].asString();

str+=fmt.str();

}


str+=getZoneRoutes(routers,jobV);

//close the main zone and platform
	str += R"(
	</zone>
</platform>
			 )";


	ofstream myfile;
myfile.open("resources/hsgPlatform.xml");

myfile<<str;
myfile.close();



ofstream deployf;
deployf.open("resources/hsgDeploy.xml");

deployf<<getDeployJson();
deployf.close();

}

/*
 * 	<host id="host2" speed="2.0Gf" core="8">
 <mount storageId="host2_disk1" name="/h2d1" />
 <mount storageId="host2_disk2" name="/h2d2" />

 </host>
 <link id="zone_1_link" bandwidth="1GBps" latency="50us" />

 <route src="host3" dst="router1">
 <link_ctn id="l3" />
 </route>
 * */

string JsonPlatform::getHostInfo(string router, Json::Value value) {
	vector<string> hdds;
	string hostName = "host" + to_string(this->hid++);
	hosts.push_back(hostName);
	string xmlStr = "";
	boost::format fmt;
	for (int i = 0; i < value["hddNums"].asInt(); i++) {
		string str0 = R"(
<storage id="%s" typeId="%s" attach="%s" />
)";
		string sId = "hdd" + hostName + to_string(i);
		hdds.push_back(sId);
		fmt = boost::format(str0) % sId % hddtype % hostName;
		xmlStr += fmt.str();
	} //tell now we attach storage to the device

	string str1 = R"(
<host id="%s" speed="%s" core="%s"> )";
	fmt = boost::format(str1) % hostName % value["cpuSpeed"].asString()
			% value["coresNum"].asString();
	xmlStr += fmt.str();

	for (int i = 0; i < value["hddNums"].asInt(); i++) {

		string str2 = R"(		<mount storageId="%s" name="%s" />
)";
		string mountName = "/mount/" + hostName + to_string(i);
		fmt = boost::format(str2) % hdds.at(i) % mountName;
		xmlStr += fmt.str();
	}

	string str3 =
			R"(
			</host>
			<link id="%s" bandwidth="%s" latency="%s" />
			<host_link id="%s" up="%s" down="%s" />

)";
	string linkId=hostName+"link";
	fmt = boost::format(str3) %linkId//link id
							%value["accessLinkSpeed"].asString()
							%value["accessLinkLatency"].asString()
							%hostName
							%linkId
							%linkId
							;
			xmlStr += fmt.str();


	return xmlStr;
}
string JsonPlatform::get_nn_or_rm(string router, Json::Value value,int h){
	vector<string> hdds;
		string hostName = "host" + to_string(h);
		string xmlStr = "";
		boost::format fmt;
		for (int i = 0; i < value["hddNums"].asInt(); i++) {
			string str0 = R"(
	<storage id="%s" typeId="%s" attach="%s" />
	)";
			string sId = "hdd" + hostName + to_string(i);
			hdds.push_back(sId);
			fmt = boost::format(str0) % sId % hddtype % hostName;
			xmlStr += fmt.str();
		} //tell now we attach storage to the device

		string str1 = R"(
	<host id="%s" speed="%s" core="%s"> )";
		fmt = boost::format(str1) % hostName % value["cpuSpeed"].asString()
				% value["coresNum"].asString();
		xmlStr += fmt.str();

		for (int i = 0; i < value["hddNums"].asInt(); i++) {

			string str2 = R"(		<mount storageId="%s" name="%s" />
	)";
			string mountName = "/mount/" + hostName + to_string(i);
			fmt = boost::format(str2) % hdds.at(i) % mountName;
			xmlStr += fmt.str();
		}

		string str3 =
				R"(
				</host>				
	<link id="%s" bandwidth="%s" latency="%s" />

	)";
		string linkId=hostName+"link";
		fmt = boost::format(str3) %linkId//link id
								%value["accessLinkSpeed"].asString()
								%value["accessLinkLatency"].asString()

								;
				xmlStr += fmt.str();


		return xmlStr;

}
string JsonPlatform::get_route_nn_rm(string router, Json::Value value,int h){

	string hostName = "host" + to_string(h);
			string xmlStr = "";
			boost::format fmt;
	string str3 =
			R"(
		<route src="%s" dst="%s">
			<link_ctn id="%s" />
		</route>

)";
	string linkId=hostName+"link";
	fmt = boost::format(str3)
							%hostName
							%router
							%linkId
							;
			xmlStr += fmt.str();


	return xmlStr;


}


string JsonPlatform::getZoneRoutes(vector<string> routers,Json::Value value){
	string str="";
	boost::format fmt;
	for(int i=0;i<routers.size()-1;i++){

		for(int j=i+1;j<routers.size();j++){
//make route from i to j router
			string tem=R"(
			<link id="%s" bandwidth="%s" latency="%s" />
					
			)";
			string lid="l_rack"+to_string(i)+"_rack"+to_string(j);
			string srcZone="rack"+to_string(i);
			string destZone2="rack"+to_string(j);
			fmt = boost::format(tem) %lid
									 % value["coreLinkSpeed"].asString()
									 % value["coreLinkLatency"].asString()
								;

str+=fmt.str();
		}
	}


	for(int i=0;i<routers.size()-1;i++){

		for(int j=i+1;j<routers.size();j++){
//make route from i to j router
			string tem=R"(
			
					<zoneRoute src="%s" dst="%s" gw_src="%s"
						gw_dst="%s">
						<link_ctn id="%s" />
					</zoneRoute>
			)";
			string lid="l_rack"+to_string(i)+"_rack"+to_string(j);
			string srcZone="rack"+to_string(i);
			string destZone2="rack"+to_string(j);
			fmt = boost::format(tem)
									 %srcZone
									 %destZone2
									 %routers.at(i)
									 %routers.at(j)
									 %lid;

str+=fmt.str();
		}
	}



	return str;
}

string JsonPlatform::getDeployJson(){
	string str="";
	boost::format fmt;
string stem=R"(<?xml version='1.0'?>
<!DOCTYPE platform SYSTEM "http://simgrid.gforge.inria.fr/simgrid/simgrid.dtd">
<platform version="4.1">

	<actor host="host1" function="ResourceManager">
		<argument value="host0_nameNode" />
	</actor>

	<actor host="host0" function="mrclient">
		<argument value="host0_nameNode" />
		<argument value="host1_ResourceManager" />
	</actor>
	 

	<actor host="host0" function="nameNode">
		<argument value="host0_nameNode" />
	</actor>

)";

str+=stem;
int jj=2;//because 0  for NN and 1 for RM
for(int i=0;i<hosts.size();i++){
	stem=R"(
	<actor host="%s" function="dataNode" />
	<actor host="%s" function="nodeManager">
<argument value="host0_nameNode" />
		<argument value="host1_ResourceManager" />
	</actor>

)";
	string hn="host"+to_string(jj++);
	fmt = boost::format(stem) %hn%hn;
	str+=fmt.str();
}


stem=R"(
</platform>
)";

str+=stem;
	return str;
}

JsonPlatform::~JsonPlatform() {
	// TODO Auto-generated destructor stub
}

