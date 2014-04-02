/*
 * jar_main.cpp
 *
 *  Created on: Sep 10, 2011
 *      Author: gigemjt
 */
#include "marble.h"
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include "vector_jar.h"
#include "llist_jar.h"
#include <iostream>
#include <fstream>
#include <map>
//------------------------------------------------------------------------------

void print_menu();
int get_menu_input();
void menu_selection(int i);
void write_jar_to_file(jar& j,string fileName);
void read_jar_from_file(jar& jar,string far);
jar::jar& get_random_jar();
jar& get_specific_jar();
void add_jar_to_list(string name,jar& j);
void print_jar_list();
void get_marble_color();
void get_marble_size();

//------------------------------------------------------------------------------
map<string,jar*> cabinet;
vector<string> keys;
string last_name_inserted;
class Bad_menu_input {}; // exception class
class Bad_jar_list_input {}; // exception class
class Bad_jar_list_input {}; // exception class
class No_marble_in_jar {};// exception class

//------------------------------------------------------------------------------

int main()
{
	srand(time(0));
	print_menu();
	int opt=get_menu_input();
	while(opt!=8)
	{
		menu_selection(opt);
		print_menu();
		opt=get_menu_input();
	}
	cout<<"program successfully exited"<<endl;
//	cout<<opt;
}

//------------------------------------------------------------------------------

void menu_selection(int i)
{
	switch(i)
	{
		case 0:{
			cout<<"Insert the number of marbles to create a jar\n";
			int i;
			cin>>i;
			jar& j=get_random_jar();
			for(int k=0;k<i;k++)
			{
				Marble m;
				j.add(m);
			}
			cout<<"Insert name of jar (no spaces)\n";
			string name;
			cin>>name;
			add_jar_to_list(name,j);
		}break;
		case 1:{
			jar& j=get_specific_jar();
			write_jar_to_file(j,last_name_inserted+".c_jar");
			}break;
		case 2:{
			//cout<<"Insert name of jar (no spaces)\n";
			jar* j2;
			try
			{
				jar& j=get_specific_jar();
				j2=&j;
			}catch(Bad_jar_list_input bjli)
			{
				jar& j=get_random_jar();
				j2=&j;
			}
			jar& j=*j2;
			read_jar_from_file(j,last_name_inserted+".c_jar");
			//cabinet.insert(pair<string,jar>(last_name_inserted,j));
			cabinet[last_name_inserted]=&j;
			}break;
		case 3:{
			get_marble_color();

			}break;
		case 4:{
			get_marble_size();
			}break;
		case 5:{
			}break;
		case 6:{
			}break;
		case 7:{
			}break;
		case 8:{
			}break;
		case 9:{
			}break;
		default:{
			cout<<"bad_menu_input: Try again"<<endl;
		}break;
	}
	//throw Bad_menu_input();
}

//------------------------------------------------------------------------------

int get_menu_input()
{
	string n;
	cin>>n;
	char &in=n[0];
	if(in=='(')
	{
		in=n[1];
	}
	int int_in=in;
	if(int_in-97<0)
	{
		int_in-=65;
	}else
	{
		int_in-=97;
	}
	return int_in;
}

//------------------------------------------------------------------------------

void print_menu()
{
	cout<<"insert the letter of the option you want ex: a"<<endl;
	cout<<" (a) Enter the number of marbles to create a jar\n";
	cout<<" (b) Print the jar to a file\n";
	cout<<" (c) Read a jar from a file\n";
	cout<<" (d) Remove a specific marble with color x\n";
	cout<<" (e) Remove a specific marble with size x\n";
	cout<<" (f) Merge 2 jars\n";
	cout<<" (g) Intersection of 2 jars\n";
	cout<<" (h) Difference of 2 jars\n";
	cout<<" (i) Exit the program\n";
	cout<<" (j) Reprint menu\n";
}

//------------------------------------------------------------------------------

void write_jar_to_file(jar& j,string file_name)
{
	cout<<file_name<<endl;
	ofstream out(file_name.c_str());

	for(int k=0;k<j.marble_number();k++)
	{
		out<<j.get_marble(k)<<endl;
	}
	/*
	while(!j.is_empty())
	{

	}
	*/
}

//------------------------------------------------------------------------------

void read_jar_from_file(jar& jar,string file_name)
{
	//jar jar1=get_random_jar();
	cout<<"input "<<file_name<<endl;
	ifstream in(file_name.c_str());
	while(!in.eof())
	{
		Marble m;
		in>>m;
		jar.add(m);
	}
}

jar::jar& get_random_jar()
{
	int type=rand()%2;
	jar::jar* da_jar;
	if(type==0)
	{
		da_jar=new vector_jar();
	}
	if(type==1)
	{
		da_jar=new llist_jar();
	}
	jar::jar& da_jar_2=*da_jar;
	return da_jar_2;
}
jar& get_specific_jar()
{
	print_jar_list();
	cout<<"insert the name of the jar you want\n";
	string n;
	cin>>n;
	last_name_inserted=n;
	map<string,jar>::iterator it;
	//it=cabinet.find(n);
	//if(it==cabinet.end())
	if(false)
	{
		throw Bad_jar_list_input();
	}else
	{
		jar* j=cabinet[n];
		 cout<<"monkeys are here"<<endl;
		return *j;
	}

}
void add_jar_to_list(string name,jar& j)
{
	cabinet[name]=&j;
	keys.push_back(name);
}
void print_jar_list()
{
	for(int k=0;k<keys.size();k++)
	{
		cout<<" Jar "<<keys[k]<<endl;
	}
}
void get_marble_color()
{
	jar& j=get_specific_jar();
	cout<<"Enter color of specified marble"<<endl;
	Marble::Color c;
	cin>>c;
	Marble out;
	int count=0;
	bool found=false;
	while(!found&&count<100)
	{
		Marble selected(c);
		for(int k=0;k<j.marble_number();k++)
		{
			if(j.get_marble(k)==selected)
			{
				out=j.get_marble(k);
				found=true;
			}
		}
		count++;
	}
	if(!found)
	{
		throw No_marble_in_jar();
	}
	cout<<"The marble is you wanted was\n"<<out<<endl;
	j.remove(out);
}
void get_marble_size()
{
	jar& j=get_specific_jar();
	cout<<"Enter color of specified marble"<<endl;
	Marble::Size c;
	cin>>c;
	Marble out;
	int count=0;
	bool found=false;
	while(!found&&count<100)
	{
		Marble selected(c);
		for(int k=0;k<j.marble_number();k++)
		{
			if(j.get_marble(k)==selected)
			{
				out=j.get_marble(k);
				found=true;
			}
		}
		count++;
	}
	if(!found)
	{
		throw No_marble_in_jar();
	}
	cout<<"The marble is you wanted was\n"<<out<<endl;
	j.remove(out);
}
