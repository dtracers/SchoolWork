// This uses Windows API CTime class (details at MSDN)

#ifndef _TIME_H_
#define _TIME_H_

#include <atltime.h>
#include <iostream>

using namespace std;

class Time {
   friend ostream& operator<<(ostream& outputStream, const Time& outputTime);
   friend bool operator==(const Time& leftTime, const Time& rightTime);
   friend bool operator!=(const Time& leftTime, const Time& rightTime);
   friend bool operator>(const Time& leftTime, const Time& rightTime);
   friend bool operator<(const Time& leftTime, const Time& rightTime);
   friend bool operator>=(const Time& leftTime, const Time& rightTime);
   friend bool operator<=(const Time& leftTime, const Time& rightTime);
private:
   CTime time;
public:
   Time();
	Time(string newTime);
};

#endif // _TIME_H_