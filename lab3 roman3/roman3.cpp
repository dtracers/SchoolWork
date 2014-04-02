/*
 * roman3.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: gigemjt
 */
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
double calculate(string g);
int get_parenthesis(string g,int index);
int get_Roman_token(string g);
int roman_to_int(char c);
string int_to_roman(int k);
void fill();
int main()
{
	fill();
	int save=0;
	while(!cin.fail()&&save<10)
	{
		string g;
		cin>>g;
		double d=calculate(g);
		cout<<"="<<d<<endl;
		save+=1;
	}
}
vector<char> Roman;
vector<char> v;
void fill()
{
	v.push_back('(');
	v.push_back('+');
	v.push_back('-');
	v.push_back('*');
	v.push_back('/');
	v.push_back('^');
	Roman.push_back('M');
	Roman.push_back('D');
	Roman.push_back('C');
	Roman.push_back('L');
	Roman.push_back('X');
	Roman.push_back('V');
	Roman.push_back('I');
}
double calculate(string g)
{
	for(int k=0;k<v.size();k++)
	{

		cout<<"the string is"<<g<<"the index is"<<k<<endl;
		int index=g.find_first_of(v[k],0);
		if(index>=0&&index<g.length())
		{
			switch(v[k])
			{
				case '(':
				{
					int end=get_parenthesis(g,index+1);
					string g2=g.substr(index+1,end-(index+1));
					double temp=calculate(g2);
					string middle=int_to_roman(((int)temp));
					middle+=".";
					cout<<"the value of whats inside"<<temp<<middle<<endl;
					string first_half="";
					if(index>0)
						first_half=g.substr(0,index);
					g=first_half+middle+g.substr(end+1);
					cout<<"after perenthesisizing"+g<<endl;
					k=-1;
				}break;
				case '+':return calculate(g.substr(0,index))+
						calculate(g.substr(index+1));

				case '-':return calculate(g.substr(0,index))-
						calculate(g.substr(index+1));

				case '*':return calculate(g.substr(0,index))*
						calculate(g.substr(index+1));

				case '/':return calculate(g.substr(0,index))/
						calculate(g.substr(index+1));

				case '^':return pow(calculate(g.substr(0,index)),
						calculate(g.substr(index+1)));
			}
		}
	}
	return get_Roman_token(g);
}
int get_parenthesis(string g,int index)//should start at the index of the ( +1
{
	string g2="";
	int counter=0;
	while(counter>=0&&index<g.length())
	{
		if(g[index]=='(')
			counter+=1;
		else if(g[index]==')')
			counter-=1;
		index++;
	}
	return index-1;
}
int get_Roman_token(string q)
{
	int ans = 0;
//	cout<<q<<"the string"<<q.find_first_of('.',0)<<"string position"<<endl;
	vector<int> arr(q.find_first_of('.',0));
	for(int k=0;k<q.find_first_of('.',0);k++)//goes through every character in the
	//Roman Numeral string and stores its number value in an array
	{
		arr[k]=roman_to_int(q[k]);
	}
	for(int k=0;k<((arr.size())-1);k++)
	{
		if(arr[k]<arr[k+1])//if the value at the index after this one is
			//greater than the value at this index (ex: this index is 1,
			//next index is 10), it will add the negative of the value at
			//this index; this is for IX (1 followed by 10 = 9 = -1 + 10)
			ans-=arr[k];
		else
			ans+=arr[k];//adds the value in the current index, so long as
			//its not a negative one
	}
	ans+=arr[arr.size()-1];//added on last so that an IndexOutOfBounds
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
string int_to_roman(int a)
{
	string ans = "";
	vector<int> nums(7);//an array to hold the ammount of the different
	//Roman Numeral digits there would be in this Arabic Numeral
	for(int k=0;k<Roman.size();k++)
	{
		int temp=roman_to_int(Roman[k]);
		nums[k]=a/temp;
		a%=temp;
	}
	for(int k=0;k<nums.size();k++)
	{
		//if there are more than 4 of a Roman Numeral
		//digit (only occurs for 900, 400, 90, 40, 9, 4 where you'll
		//have 4 C, 4 X, or 4 I)
		if(nums[k]>=4&&k!=0)
		{
			//if there is one of the previous digit (ex
			//900 (1 D, 4 C), 90 (1 L 4 X), 9 (1 V, 4 I)
			if(nums[k-1]==1)
			{
				switch(k)
				{
					case 2:     ans+="\bCM"; break;
					case 4:     ans+="\bXC"; break;
					case 6:     ans+="\bIX"; break;
				  //use if the above doesn't work (doesn't print right)
				  //case 2:     ans=ans.substring(0,ans.length()-1)+"CM"; break;
				  //case 4:     ans=ans.substring(0,ans.length()-1)+"XC"; break;
				  //case 6:     ans=ans.substring(0,ans.length()-1)+"IX"; break;
				}
			}
			//if there is none of the previous digit (ex 400 (0D, 4C),
			//40 (0L, 4X), 4 (0V, 4I)
			else
			{
				switch(k)
				{
					case 2:     ans+="CD"; break;//adds the compound form
					//of these number (900 = 1000-100 = CD); no need to
					//delete previous character b/c there is no previous
					//digit
					case 4:     ans+="XL"; break;
					case 6:     ans+="IV"; break;
				}
			}
		}
		else//if there is a normal ammount of digits (defined as follows)
			//M:inf
			//D:1
			//C:<=3
			//L:1
			//X:<=3
			//V:1
			//I:<=3
		{
			for(int j=0;j<nums[k];j++)//a loop to run the ammount of times each digit appears
			{
				switch(k)
				{
					case 0:     ans+="M"; break;//adds the digit to the string
					case 1:     ans+="D"; break;
					case 2:     ans+="C"; break;
					case 3:     ans+="L"; break;
					case 4:     ans+="X"; break;
					case 5:     ans+="V"; break;
					case 6:     ans+="I"; break;
				}
			}
		}
	}
	return ans;
}
