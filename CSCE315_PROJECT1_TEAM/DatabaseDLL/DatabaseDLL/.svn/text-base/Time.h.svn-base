/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The Time header file
 Learn more at http://goo.gl/lTVVA
*/
#ifndef __Time_H_
#define __Time_H_

#include <iostream>
#include "DatabaseException.h"

using namespace std;

class Time {
public:
	//Constructor
	Time();
	Time(const Time& t);
	Time(int hr, int min, int sec);
	~Time();

	//Accessor function
	int getMinutes() const {
		return minute;
	}
	int getHours() const {
		return hour;
	}
	int getSeconds() const {
		return second;
	}
	string toString();

private:
	int minute;
	int hour;
	int second;
};

//Helper Function
bool isTime(int hour, int minute, int second);

bool operator==(const Time& time1, const Time& time2);

bool operator!=(const Time& time1, const Time& time2);

bool operator<(Time& time1, Time& time2);

bool operator>(Time& time1, Time& time2);

bool operator<=(Time& time1, Time& time2);

bool operator>=(Time& time1, Time& time2);

ostream& operator<<(ostream& os, Time& time);

istream& operator>>(istream & is, Time& t);

#endif
