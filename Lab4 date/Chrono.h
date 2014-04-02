/*
 * Chrono.h
 *
 *  Created on: Oct 12, 2010
 *      Author: gigemjt
 */
/*
#ifndef CHRONO_H_
#define CHRONO_H_


#endif /* CHRONO_H_ */
/**/
#include <iostream>

namespace Chrono
{

	using namespace std;
	class Date{
	public:
		enum Season
		{
			spring=1,summer=2,fall=3,winter=4
		};
		enum Month
		{
			jan=1, feb=2, mar=3, apr=4, may=5, jun=6, jul=7, aug=8, sep=9, oct=10, nov=11, dec=12
		};

		typedef int Year;

		class Invalid{};  //to throw as exception

		Date(Year y, Month m, int d);
		Date();

		int day() const{return d;}
		Month month() const{return m;}
		int year() const{return y;}
		string season() const;
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);
	private:
		int y;
		Month m;
		int d;
	};

	int days_in_month(int y,Date::Month m,int d);

	bool is_date(int y, Date::Month m, int d);

	bool leapyear(int y);

	bool check(int y, Date::Month m, int d);

	Date::Month operator+(Date::Month& m,Date::Month& i);

	Date::Month operator++(Date::Month& m);

	bool operator==(const Date& a, const Date& b);

	bool operator!=(const Date& a, const Date& b);

	string month_to_string(Date::Month m);

	ostream& operator<<(ostream & os, Date& d);

	istream& operator>>(istream & is, Date& d);
}
