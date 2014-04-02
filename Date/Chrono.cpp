/*
 * Chrono.cpp
 *
 *  Created on: Oct 12, 2010
 *      Author: gigemjt
 */

#include "Chrono.h"

namespace Chrono
{
	Date::Date(Year yy, Month mm, int dd)
		:y(yy), m(mm), d(dd)
	{
		if(!check(yy,mm,dd))throw Invalid();
	}
	Date::Date(){}
/*
	const Date* default_date()
	{
		const Date *p = new const Date dd(2001, Date::jan, 1);
		return p;
	}
	Date::Date():y(default_date().year()), m(default_date().month()), d(default_date().day())
	{
	}
*/
	void Date::add_day(int n)
	{
		int number_days_in_month=days_in_month(y,m,d);
		int new_day=d+n;
		if(new_day>number_days_in_month)
		{
			new_day-=number_days_in_month;
			add_month(1);
		}
		d=new_day;
	}
	void Date::add_month(int n)
	{
		int n_temp=n%12;
		add_year(n/12);
		int days_in_new_month=days_in_month(y,Date::Month(m+n_temp>12?(m+n_temp-12):m+n_temp),d);
		int n2=0;
		if(days_in_new_month<d)
		{
			d-=days_in_month(y,m,d);
			n2+=1;
		}else
		{
		//	cout<<days_in_new_month<<" "<<d<<endl;
		}
		if(m+n_temp>12)
			add_year(1);
		m=Month(m+n_temp>12?(m+n_temp-12):m+n_temp);
	}
	void Date::add_year(int n)
	{
		if(m==feb && d==29 && !leapyear(y+n))
		{
			m=mar;
			d=1;
		}
		y+=n;
	}
	int days_in_month(int y,Date::Month m,int d)
	{
		int days_in_month=30;

		switch(m)
		{
			case Date::jan: case Date::mar: case Date::may: case Date::jul: case Date::aug: case Date::oct: case Date::dec:
			{
				days_in_month=31;
				break;
			}
			case Date::feb:
			{
				days_in_month=(leapyear(y))?29:28;
				break;
			}
			default:
				days_in_month=30;
		}
		return days_in_month;
	}
	bool is_date(int y, Date::Month m, int d)
	{
		if(d<=0)return false;
		int number_days_in_month=days_in_month(y,m,d);
		if(number_days_in_month<d)return false;
			return true;
	}
	bool leapyear(int y)
	{
		return (y%4==0);
	}

	bool check(int y, Date::Month m, int d)
	{
		if(y<=0)
			return false;
		if(d>31||d<0)
			return false;
		if(m<1||m>12)
			return false;
		return is_date(y,m,d);
	}
	Date::Month operator++(Date::Month& m)
	{
		m=(m==Date::dec)?Date::jan:Date::Month(m+1);
		return m;
	}
	bool operator==(const Date& a, const Date& b)
	{
		return a.year()==b.year() && a.month()==b.month() && a.day()==b.day();
	}
	bool operator!=(const Date& a, const Date& b)
	{
		return !(a==b);
	}

	ostream& operator<<(ostream & os, Date& d)
	{
		return os<<'('<<d.year()<<','<<month_to_string(d.month())<<','<<d.day()<<')';
	}

	istream& operator>>(istream & is, Date& dd)
	{
		int y, d;
		//Date::Month m;
		int m;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if(!is)return is;
		if(ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')')
		{
			is.clear(ios_base::failbit);
			return is;
		}
		dd = Date(y,Date::Month(m),d);
		return is;
	}

	enum Day{sunday=0, monday=1, tuesday=2, wednesday=3, thursday=4, friday=5, saturday=6};
/*
	Day day_of_week(const Date& d)
	{
		//...
	}

	Date next_sunday(const Date& d)
	{
		//...
	}
	Date next_weekday(const Date& d)
	{
		//...
	}
*/
} //Chrono
