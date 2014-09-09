/*
 * Pi.h
 *
 *  Created on: 30.10.2014
 *      Author: ada
 */

#ifndef PI_H_
#define PI_H_
#include <ctime>
#include <iostream>
#include "arduPi.h"
#include "CAN.h"



class Pi {
public:
	void setup();
	bool isLeapYear(int year);
	int BCDToInt(byte bcd);
	int dayOfWeek(int y, int m, int d);
	int dayOfYear(int y, int m, int d);
	std::tm* requestTime();
	std::time_t requestTimeSinceEpoch();

};

#endif /* PI_H_ */
