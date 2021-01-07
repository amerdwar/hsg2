/*
 * Capacity.h
 *
 *  Created on: Dec 20, 2020
 *      Author: amer
 */

#ifndef YARN_CAPACITY_H_
#define YARN_CAPACITY_H_
#include <string>
#include <vector>
using namespace std;
class Capacity {
public:
	string name;
	int percent;


	Capacity(string name,int percent);
	virtual ~Capacity();
};

#endif /* YARN_CAPACITY_H_ */
