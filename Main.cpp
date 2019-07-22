/*
 * Main.cpp
 *
 *  Created on: Jan 3, 2019
 *      Author: alpha
 */

#include <simgrid/s4u.hpp>
#include <gtest/gtest.h>
//#include "mapreduce/Counter.h"
#include "hdfs/NameNode.h"
#include "hdfs/DataNode.h"
#include "hdfs/Client.h"
#include "yarn/ResourceManager.h"
#include "yarn/NodeManager.h"
#include "mapreduce/MRClient.h"
#include "resources/JsonPlatform.h"
XBT_LOG_NEW_DEFAULT_CATEGORY(Main, "Messages specific for this example");


int factory(int a){
	int t=1;
	for (int i=1;i<=a;i++)
		t*=i;
	return t;
}

int orders(int n,int q){
	int res=1;
	int t=n;
	for (int i=1;i<=q;i++){
	res*=t;
	t--;
	}
	return res;
}

double combination(int n,int q){
	int res;
	if (q==0)
		return 1;
	res=orders(n,q)/factory(q);

	return res;
}



double getSub(int64_t i, int64_t q,int64_t n){
double s=0;
if (i==0)
	return 0;
	else
	{
for (int j=i-1;j>0;j--){
	//cout<<" -  c("<<i<<","<<j<<") * ( "<<j<<"^"<<n<<"-";
	s+=combination(i,j)*(pow(j,n)-getSub(j,q,n));
	//cout<<")";
}
	return s;
	}
}

double combinedRec(double n,double q){

double  sum=0;
double test=q;
if (q>n)
	test=n;
for(int i=1;i<=test;i++){
//	cout<<"  c("<<q<<","<<i<<") * ( "<<i<<"^"<<n<<"";
	double tem=combination(q,i)*(pow(i,n)-getSub(i,q,n));
//cout<<")"<<endl;

	sum+=tem;
	cout <<tem<<endl;
}
cout<<sum<<endl;
	return sum;

}

void doSim(int argc, char* argv[]) {

	simgrid::s4u::Engine e(&argc, argv);
//	xbt_assert(argc > 2, "Usage: %s platform_file deployment_file\n", argv[0]);

	/* Register the classes representing the actors */

	e.register_actor<NameNode>("nameNode");
	e.register_actor<Client>("client");
	e.register_actor<DataNode>("dataNode");
	e.register_actor<ResourceManager>("ResourceManager");
	e.register_actor<MRClient>("mrclient");

	e.register_actor<NodeManager>("nodeManager");

	/* Load the platform description and then deploy the application */
	//e.load_platform(argv[1]);
	//e.load_deployment(argv[2]);

	e.load_platform("resources/hsgPlatform.xml");
	e.load_deployment("resources/hsgDeploy.xml");


	//simgrid::s4u::Actor::create("client", simgrid::s4u::Host::by_name("host1"), Client("host2_nameNode"));

	/* Run the simulation */
	e.run();

	XBT_INFO("**************END OF SIMULATION  ****************");

}

double secondForm(double n,double q){
	double s=0;
//C(n,k) * Sum_{j=0..k} (-1)^(k-j) * C(k,j) * j^n.

double a=q;
if(q>n)
	a=n;
	for (double i=1;i<=a;i++){
		double innerSum=0;
	for (double j=1;j<=i;j++){
		innerSum+=pow (-1,i-j+1)*combination(i,j)*pow(j,n);
	}

		double tem =combination(q,i)*innerSum;
		cout<<tem<<endl;
		s+=tem;


	}
	cout<<endl<<s<<endl;
	return s;

}
int main(int argc, char* argv[]) {
//	testing::InitGoogleTest(&argc, argv);
	//JsonPlatform* jp=new JsonPlatform();
	//jp->creatPlatform("resources/cluster/cluster.json");
	//doSim(argc, argv);
//	RUN_ALL_TESTS();
secondForm(4,4);
	//double d=combinedRec(5,6);
//int d2=combination(11,3)*3;
//int d3=combination(6,3)*3;
//XBT_INFO("this is the ddd: %s",d);
//XBT_INFO("this is the ddd: %s",to_string(d).c_str());
//XBT_INFO("this is the ddd: %s",to_string(d3).c_str());

	return 0;
}





