/*
 * meses.cpp
 *
 *  Created on: Oct 14, 2010
 *      Author: gigemjt
 */
#include"Chrono.h"
using namespace Chrono;
int main()
{
	Date d=Date(1900,Date::Month(1),1);
	for(int k=0;k<12;k++)
	{
		cout<<d<<endl;
		d.add_month(1);
	}
}
string Chrono::month_to_string(Date::Month m)
{
	switch(m)
	{
		case 1:return "enero";
		case 2:return "febrero";
		case 3:return "marzo";
		case 4:return "abril";
		case 5:return "mayo";
		case 6:return "junio";
		case 7:return "julio";
		case 8:return "agosto";
		case 9:return "septiembre";
		case 10:return "octubre";
		case 11:return "noviembre";
		case 12:return "diciembre";
		default:return "no hable engles";
	}
}
