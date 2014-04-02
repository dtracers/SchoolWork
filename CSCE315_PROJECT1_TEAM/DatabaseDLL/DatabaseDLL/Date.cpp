/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The Date class for date columns
 Learn more at http://goo.gl/lTVVA
 */
#include "Date.h"

Date::Date() {
	y=1970;
	m=1;
	d=1;
}
Date::Date(const Date& d) {
	y = d.y;
	m = d.m;
	this->d = d.d;
}
Date::Date(int yyyy, int mm, int dd) {
	if (!isDate(yyyy, mm, dd))
	{
		cout<<"WARNING DATE IS NOT VALID"<<endl;
	}/*
		throw DatabaseException(40,
				dd + '/' + mm + '/' + yyyy + " is not a valid date.");
*/
	y = yyyy;
	m = mm;
	d = dd;
}
Date::~Date() {

}

string Date::toString() {
	stringstream y;
	y << getYear();
	stringstream m;
	m << getMonth();
	stringstream d;
	d << getDay();

	string output = "";
	output += y.str();
	output += '/';
	output += m.str();
	output += '/';
	output += d.str();
	return output;
}

//Checks if the month and number of days is valid
bool isDate(int y, int m, int d) {
	if (d <= 0) {
		return false;
	}

	int daysInMonth;

	switch (m) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: {
		daysInMonth = 31;
		break;
	}
	case 2: {
		daysInMonth = (isLeapYear(y)) ? 29 : 28;
		break;
	}
	case 4:
	case 6:
	case 9:
	case 11:
		daysInMonth = 30;
		break;
	default:
		return false;
	}

	if (daysInMonth >= d) {
		return true;
	}

	return false;
}

//Returns true if the year is a leap year
bool isLeapYear(int y) {
	//A leap year is divisable by 4, but not by 100 (except if divisable by 400.)
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
		return true;
	} else
		return false;
}

//Operator overloads for ==, !=, <, >, <=, >=, <<, >>
bool operator==(const Date& a, const Date& b) {
	return a.getYear() == b.getYear() && a.getMonth() == b.getMonth()
			&& a.getDay() == b.getDay();
}
bool operator!=(const Date& a, const Date& b) {
	return !(a == b);
}

bool operator<(Date& date1, Date& date2) {
	int day1 = date1.getDay();
	int month1 = date1.getMonth();
	int year1 = date1.getYear();
	int day2 = date2.getDay();
	int month2 = date2.getMonth();
	int year2 = date2.getYear();

	if (year1 < year2) {
		return true;
	} else if (year1 > year2) {
		return false;
	} else if (month1 < month2) {
		return true;
	} else if (month1 > month2) {
		return false;
	} else if (day1 < day2) {
		return true;
	} else if (day1 > day2) {
		return false;
	} else {
		return false;
	}
}

bool operator>(Date& date1, Date& date2) {
	int day1 = date1.getDay();
	int month1 = date1.getMonth();
	int year1 = date1.getYear();
	int day2 = date2.getDay();
	int month2 = date2.getMonth();
	int year2 = date2.getYear();

	if (year1 > year2) {
		return true;
	} else if (year1 < year2) {
		return false;
	} else if (month1 > month2) {
		return true;
	} else if (month1 < month2) {
		return false;
	} else if (day1 > day2) {
		return true;
	} else if (day1 < day2) {
		return false;
	} else {
		return false;
	}
}

bool operator<=(Date& date1, Date& date2) {
	if ((date1 < date2) || (date1 == date2)) {
		return true;
	} else {
		return false;
	}
}

bool operator>=(Date& date1, Date& date2) {
	if ((date1 > date2) || (date1 == date2)) {
		return true;
	} else {
		return false;
	}
}

ostream& operator<<(ostream & os, Date& d) {
	return os << d.getYear() << '/' << d.getMonth() << '/' << d.getDay();
}

istream& operator>>(istream & is, Date& dd) {
	int y;
	int d;
	int m;
	char ch1, ch2;

	is >> y >> ch1 >> m >> ch2 >> d;
	if (!is)
		return is;
	if (ch1 != '/' || ch2 != '/') {
		is.clear(ios_base::failbit);
		return is;
	}
	dd = Date(y, m, d);
	return is;
}
