/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The Date header file
 Learn more at http://goo.gl/lTVVA
*/
#ifndef __Date_H_
#define __Date_H_

#include <iostream>
#include "DatabaseException.h"
#include <sstream>

using namespace std;

class Date {
public:
	//Constructor
	Date();
	Date(const Date& d);
	Date(int yyyy, int mm, int dd);
	~Date();

	//assessor functions
	int getDay() const {
		return d;
	}
	int getMonth() const {
		return m;
	}
	int getYear() const {
		return y;
	}

	string toString();

private:
	int y;
	int m;
	int d;
};

//Helper Functions
bool isDate(int y, int m, int d);

bool isLeapYear(int y);

bool operator==(const Date& a, const Date& b);

bool operator!=(const Date& a, const Date& b);

bool operator<(Date& date1, Date& date2);

bool operator>(Date& date1, Date& date2);

bool operator<=(Date& date1, Date& date2);

bool operator>=(Date& date1, Date& date2);

ostream& operator<<(ostream & os, Date& d);

istream& operator>>(istream & is, Date& dd);

#endif
