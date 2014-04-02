/*
 * Fibo_main.cpp
 *
 *  Created on: Sep 19, 2011
 *      Author: gigemjt
 */
//#include"stringInt.h"
using namespace std;
#include<iostream>
#include<fstream>
int convert(string g);
string convert(int t);
int convert(char g);
int get_number_from_string(string g,int index);
string add_strings(const string& lhs,const string& rhs);

string converter="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()<>,.?/:;{[}]|_-+=";
int base=64;//converter.size();

int main()
{

	string prev("0");
	string two("1");
	string new_one("0");
	ofstream outst("10000 fibo.txt");
	for(int k=1;k<=10000;k++)
	{
		new_one=add_strings(prev,two);
		outst<<" iteration "<<k<<" = "<<new_one<<endl;
		cout<<" iteration "<<k<<" = "<<new_one<<endl;

		prev=two;
		two=new_one;
	}
	cout<<"done the final one is "<<new_one<<endl;
}


string add_strings(const string& lhs2,const string& rhs2)
{
	int max=lhs2.size();
	int min=lhs2.size();
	bool left_max=true;
	if(rhs2.size()>max)
	{
		left_max=false;
		max=rhs2.size();
	}
	if(rhs2.size()<min)
	{
		left_max=true;
		min=rhs2.size();
	}
	int offset=max-min;
	int carry=0;
	string new_number;
	for(int k=max-1;k>=0;k--)
	{
		int left,right;
		if(left_max)
		{
			left=get_number_from_string(lhs2,k);
			right=get_number_from_string(rhs2,k-offset);
		}else
		{
			left=get_number_from_string(lhs2,k-offset);
			right=get_number_from_string(rhs2,k);
		}
		int total=left+right+carry;
		carry=0;
		if(total>=base)
		{
			carry+=1;
			total-=base;
		}
		new_number=convert(total)+new_number;

	}
	if(carry>0)
		new_number=convert(carry)+new_number;
	return new_number;
}

int get_number_from_string(string g,int index)
{
	if(index<0)
	{
		return 0;
	}else
	{
		char c=g[index];
		return convert(c);
	}
}

int convert(string g)
{
	for(int k=61;k<converter.size();k++)
	{
		if(converter[k]==g[0])
		{
			return k;
		}
		if(k>=base)
		{
			cout<<"Wally Theodore Fedric"<<endl;
		}
	}
	cout<<" the thing that wasnt present["<<g<<"]"<<endl;
	cout<<"not present"<<endl;
	return 1/0;
}
int convert(char g)
{
	int g2=(int)g;
	if(g2>=48&&g2<=57)
	{
		return g2-48;
	}else if(g2>=65&&g2<=90)
	{
		return g2-55;//-65+10
	}else if(g2>=97&&g2<=122)
	{
		return g2-87;//-97+10
	}else
	{
		string g3;
		g3+=g;
		return convert(g3);//all the rest
	}
}
string convert(int t)
{
	char c=converter[t];
	string g;
	g+=c;
	return g;
}

