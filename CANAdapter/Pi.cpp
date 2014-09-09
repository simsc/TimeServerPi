/*
 * Pi.cpp
 *
 *  Created on: 30.10.2014
 *      Author: ada
 */

#include "Pi.h"
#include "CAN.h"
#include "arduPi.h"

const int IDWAITED = 2;
const int OWNID = 3;

CAN myCan = CAN();

void Pi::setup() {
	myCan.begin(500);
}

bool Pi::isLeapYear(int year) {
	if (year % 4 == 0) {
		if (year % 100 == 0) {
			if (year & 400 == 0) {
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

int Pi::BCDToInt(byte bcd) {

	int a = bcd & 15;
	int b = bcd & 240;
	return a + 10 * b;

}

/** 0 = Sonntag */
int Pi::dayOfWeek(int y, int m, int d) {
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

	y -= m < 3;

	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

int Pi::dayOfYear(int y, int m, int d) {
	static int t[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int result = 0;
	for (int i = 0; i < m-1; ++i) {
		result += t[i];
	}
	if (isLeapYear(y) && m > 2) {
		++result;
	}
	result += d - 1;
	return result;
}



/**
 * Sendet eine Anfrage für die Zeit
 */
std::tm* Pi::requestTime() {

	myCan.messageTx.id = OWNID;
	myCan.messageTx.data[0] = 42;
	myCan.sendMessage(&myCan.messageTx);

	while (true) {
		if (myCan.messageAvailable() == 1) {
			myCan.getMessage(&myCan.messageRx);
			if (myCan.messageRx.id == IDWAITED) {
				if (myCan.messageRx.header.length == 6)
					break;
			}
		}
	}

	std::tm* time = new std::tm;

	//Sekunden
	byte timeData = myCan.messageRx.data[0];
	time->tm_sec = BCDToInt(timeData & 127);

	//Minuten
	timeData = myCan.messageRx.data[1];
	time->tm_min = BCDToInt(timeData & 127);

	//Stunden und MESZ
	timeData = myCan.messageRx.data[2];
	time->tm_isdst = timeData & 64;
	time->tm_hour = BCDToInt(timeData & 63);

	//Kalendertag
	timeData = myCan.messageRx.data[3];
	time->tm_mday = BCDToInt(timeData & 63);

	//Wochentagsnummer und Monatsnummer
	timeData = myCan.messageRx.data[4];
	time->tm_wday = (timeData & 7) % 7;

	byte tmp = timeData & 248;
	tmp = tmp >> 3;
	time->tm_mon = BCDToInt(tmp - 1);

	//Jahr
	timeData = myCan.messageRx.data[5];

	int year = BCDToInt(timeData);
	while (dayOfWeek(year + 1900, time->tm_mon+1, time->tm_mday) != time->tm_wday) {
		year += 100;
	}

	time->tm_year = year;
	time->tm_yday = dayOfYear(time->tm_year, time->tm_mon+1, time->tm_mday);

	return time;
}

std::time_t Pi::requestTimeSinceEpoch(){
	std::tm* time = new std::tm;
	time = requestTime();
	return mktime(time);
}

void loop() {

}

//int main() {
//	std::cout << dayOfWeek(2014, 11, 11) << std::endl;;
//	std::cout << dayOfYear(2014, 1, 4) << std::endl;
//	setup();
//	while (1) {
//		loop();
//	}
//	return (0);
//}
