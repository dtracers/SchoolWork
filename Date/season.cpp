/*
 * season.cpp
 *
 *  Created on: Oct 12, 2010
 *      Author: gigemjt
 */
#include"Chrono.h"
using namespace Chrono;
int main()
{
	Date d=Date(1900,Date::Month(1),1);
	for(int k=0;k<12;k++)
	{
		cout<<d.season()<<endl;
		cout<<d<<endl;
		d.add_month(1);
	}
	return 0;
}

string Date::season() const
{
	if((m)<3||m==12)
	{
		return "winter";
	}
	if((m)>=3&&(m)<=5)
	{
		return "spring";
	}
	if((m)>=6&&(m)<=8)
	{
		return "summer";
	}
	if((m)>=9&&(m)<=11)
	{
		return "fall";
	}
	return "spring";
};
string Chrono::month_to_string(Date::Month m)
{
	int temp=m;
	return ""+temp;
};
