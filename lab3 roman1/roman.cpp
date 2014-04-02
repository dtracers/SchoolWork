/*
 * roman.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: gigemjt
 */
#include<iostream>
using namespace std;
int roman_to_int(char c);
int main()
{
	while(!cin.fail())
	{
		cout<<"Enter a single Roman character and press enter"<<endl;;
		char c;
		cin.get(c);
		cout<<roman_to_int(c)<<endl;;
	}
}
int roman_to_int(char c)
{
	int temp=0;
	switch(c)
	{
		case 'm':
		case 'M':   temp=1000; break;
		case 'd':
		case 'D':   temp=500; break;
		case 'c':
		case 'C':   temp=100; break;
		case 'l':
		case 'L':   temp=50; break;
		case 'x':
		case 'X':   temp=10; break;
		case 'v':
		case 'V':   temp=5; break;
		case 'i':
		case 'I':   temp=1; break;

		default :	temp=0; break;
	}
	return temp;
}
