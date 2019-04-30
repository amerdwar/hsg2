/*
 * JsonPlatform.cpp
 *
 *  Created on: Apr 30, 2019
 *      Author: alpha
 */

#include "JsonPlatform.h"

JsonPlatform::JsonPlatform() {
	// TODO Auto-generated constructor stub

}
void JsonPlatform::creatPlatform(string file) {
string str;
	Json::Value jobV;
	std::ifstream jsonFile(file);
	jsonFile >> jobV;

NameNode::chunkSize=jobV["chunkSize"].asInt64();
Hdd::readAccess=jobV["readAccess"].asDouble();
Hdd::writeAccess=jobV["writeAccess"].asDouble();
Hdd::hddSlice=jobV["hddSlice"].asDouble();


	vector<string> routers;
	boost::format fmt;
	hddtype="single_hdd";
routers.push_back("router0");
	string tem =
			R"(
<?xml version='1.0'?>
<!DOCTYPE platform SYSTEM "http://simgrid.gforge.inria.fr/simgrid/simgrid.dtd">
<platform version="4.1">

	<zone id="AS0" routing="Full">

	<zone id="rack0" routing="Full">
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

			<route src="%s" dst="%s">
				<link_ctn id="%s" />
			</route>

	)";
		string linkId=hostName+"link";
		fmt = boost::format(str3) %linkId//link id
								%value["accessLinkSpeed"].asString()
								%value["accessLinkLatency"].asString()
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
					<zoneRoute src="%s" dst="%s" gw_src="%s"
						gw_dst="%s">
						<link_ctn id="%s" />
					</zoneRoute>
			)";
			string lid="link_zone"+to_string(i)+"_zone"+to_string(j);
			string srcZone="zone"+to_string(i);
			string destZone2="zone"+to_string(j);
			fmt = boost::format(tem) %lid
									 % value["coreLinkSpeed"].asString()
									 % value["coreLinkLatency"].asString()
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


	return str;
}

JsonPlatform::~JsonPlatform() {
	// TODO Auto-generated destructor stub
}
