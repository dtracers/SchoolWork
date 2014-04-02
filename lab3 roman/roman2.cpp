/*
 * roman2.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: gigemjt
 */
#include <vector>
#include <iostream>
#include <string>
using namespace std;
int get_Roman_token();
int roman_to_int(char c);
int main()
{
	while(!cin.fail())
	{
		cout<<"enter roman numeral followed by a period"<<endl;
		cout<<get_Roman_token()<<endl;
	}
}
int get_Roman_token()
{
	string q="";
	cin>>q;
	int ans = 0;
	vector<int> arr(q.find_first_of('.',0));
	//goes through every character in the
	//Roman Numeral string and stores its number value in an array
	for(int k=0;k<q.find_first_of('.',0);k++)
	{
		arr[k]=roman_to_int(q[k]);
	}
	for(int k=0;k<((arr.size())-1);k++)
	{
		//if the value at the index after this one is
		//greater than the value at this index (ex: this index is 1,
		//next index is 10), it will add the negative of the value at
		//this index; this is for IX (1 followed by 10 = 9 = -1 + 10)
		if(arr[k]<arr[k+1])
			ans-=arr[k];
		else
			ans+=arr[k];
		//adds the value in the current index, so long as
		//its not a negative one
	}
	ans+=arr[arr.size()-1];
	//added on last so that an IndexOutOfBounds
	//doesnt occur in the above code
	return ans;
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
