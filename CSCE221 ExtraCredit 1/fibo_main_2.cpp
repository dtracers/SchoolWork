/*
 * fibo_main_2.cpp
 *
 *  Created on: Sep 19, 2011
 *      Author: gigemjt
 */
#include<vector>
#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;
vector<signed int> add_num(vector<signed int> lhs,vector<signed int> rhs);

int main()
{

	clock_t t1,t2;
	vector<signed int> prev;
	vector<signed int> two;
	vector<signed int> new_one;
	prev.push_back(0);
	two.push_back(1);
	int max=100000;
	ofstream outst(max+"_fibo2.txt");
	t1=clock();
	cout<<numeric_limits<signed int>::max()<<endl;
	for(int k=1;k<=max;k++)
	{
		new_one=add_num(prev,two);
		prev=two;
		two=new_one;
		//cout<<k<<endl;
	}
	t2=clock();
	double diff=(double)(t2-t1)/CLOCKS_PER_SEC;
	cout<<"it took "<<diff<<" seconds to get to the "<<max<<"th fibonacci sequence"<<endl;
	cout<<"done final is ";
	for(int k=0;k<new_one.size();k++)
	{
		outst<<new_one[k]<<" ";
		cout<<new_one[k]<<" ";
	}
	cout<<endl;
}

vector<signed int> add_num(vector<signed int> lhs,vector<signed int> rhs)
{
	int max=lhs.size();
	int min=lhs.size();
	bool left_max=true;
	if(rhs.size()>max)
	{
		left_max=false;
		max=rhs.size();
	}
	if(rhs.size()<min)
	{
		left_max=true;
		min=rhs.size();
	}
	int offset=max-min;
	signed int carry=0;
	vector<signed int> new_number(max);
	for(int k=max-1;k>=0;k--)
	{
		int left,right;
		if(left_max)
		{
			left=lhs[k];
			if(k-offset<0)
				right=0;
			else
				right=rhs[k-offset];
		}else
		{
			right=rhs[k];
			if(k-offset<0)
				left=0;
			else
				left=lhs[k-offset];

		}
		signed int total=left+right+carry;
		carry=0;
		while(total<0)//to catch a numerical overflow so it will go to the next increment
		{
			signed int new_total=numeric_limits<signed int>::max()+total;
			total=new_total;
			total+=2;
			carry=1;
		}

		new_number[k]=total;
	}
	if(carry>0)
		new_number.insert(new_number.begin(),carry);
	return new_number;
}
