// This uses Windows API CTime class (details at MSDN)

#ifndef _DATE_H_
#define _DATE_H_

#include <atltime.h>
#include <iostream>

using namespace std;

class Date {
	friend ostream& operator<<(ostream& outputStream, const Date& outputDate);
	friend bool operator==(const Date& leftDate, const Date& rightDate);
	friend bool operator!=(const Date& leftDate, const Date& rightDate);
	friend bool operator>(const Date& leftDate, const Date& rightDate);
	friend bool operator<(const Date& leftDate, const Date& rightDate);
	friend bool operator>=(const Date& leftDate, const Date& rightDate);
	friend bool operator<=(const Date& leftDate, const Date& rightDate);
private:
	CTime date;
public:
	Date();
	Date(string newDate);
};

#endif // _DATE_H_
