#include <iostream>
#include <fstream>
//#include "RuntimeException.h"
#include "Equation_Parser.h"
//#include "LinkedList.cpp"
#include "Evaluator.h"



using namespace std;

void printoptions();
void addOptions();
bool input();

string filename="Options";
map<string,int> options;
map<string,Equation_Parser*> operations;
int noname_in=0;
int noname_out=0;

int main() {
	addOptions();
	printoptions();
	LinkedStack<Equation_Parser> equations;
	cerr<<"Enter input"<<endl;
	while(input())
	{
		cerr<<"Enter input"<<endl;
	}
}
void addOptions()
{
	ifstream ifs (filename.c_str(), ifstream::in );
	 int option_num=0;
	 int option_num2=0;
	while(!ifs.eof())
	{
	 string str="";
	 getline (ifs,str);
	 if(str[0]=='#')//ignore
		 continue;
	 stringstream ss(str);
	 option_num=0;
	 ss>>option_num;
	 if(option_num2==0&&option_num!=0)
		 option_num2=option_num;
	 string s;
	 string option_string="";
	 if(option_num==0)
	 {
		 string subbed;
		 if(str.substr(0,4)=="Key:")
		 {
			 subbed=str.substr(4,str.size());
		//	 cerr<<"subbed0 "<<subbed<<endl;
			 int beg_space=0;
			 while(subbed[beg_space]==' ')
			 {
				 beg_space++;
			 }
			 subbed=subbed.substr(beg_space,subbed.size());
		//	 cerr<<"subbed1 "<<subbed<<endl;
			 option_string=subbed.substr(0,subbed.find_first_of(' '));
		//	 cerr<<"option_string is "<<option_string<<" /"<<endl;
			 options[option_string]=option_num2;
		//	 cerr<<"value at "<<option_string<<" is: "<<options[option_string]<<endl;
			 option_num2=0;
		 }

	 }
	 //options.insert(option_string,option_num);

	}
}
void printoptions()
{
	 ifstream ifs (filename.c_str(), ifstream::in );
	 while(!ifs.eof())
	 {
		 string str="";
		 getline (ifs,str);
		 if(str[0]=='#')//ignore
			 continue;
		 stringstream ss(str);
		 int option_num=0;
		 ss>>option_num;
		 if(option_num==0)
		 {
			 if(str.substr(0,4)=="Key:")
				 cerr<<""<<str<<endl;
			 else
				 cerr<<"\t"<<str<<endl;
		 }else
		 {
			 cerr<<"\nOption # "<<option_num<<":\t";
		 }
	 }
}
bool input()
{
	string str="";
	getline(cin,str);
	string st2;
	string input="";
	int index=str.find_first_of(' ');
	st2=str.substr(0,index);
	if(index+1<str.size())
		input=str.substr(index+1,str.size());
	int option_num=0;
	map<string,int>::iterator it;
	it=options.find(st2);
	if(it!=options.end())
	option_num=options[st2];
	switch(option_num)
	{
		case 1://assign
		{
			int in_index=input.find_first_of(' ');
			if(in_index>=input.size())
			{
				cerr<<"This input was not formatted correctly"<<endl;
			}else
			{
				string name=input.substr(0,in_index);
				string equation=input.substr(in_index+1,input.size());
				Equation_Parser* parse=new Equation_Parser(equation);
				bool success=parse->parse_now();
				if(!success)
				{
					cerr<<"parsing failed"<<endl;
				}else
					operations[name]=parse;
			}
			cerr<<"I am done with assigning"<<endl;
		}break;
		case 3:
		{
			printoptions();
		}break;
		case 4://eval
		{
			string name=input;
			if(input==""||input==str)
			{
				name="no_name";
			}
			map<string,Equation_Parser*>::iterator it;
				it=operations.find(name);
			Equation_Parser* parse;
			if(it!=operations.end())
				parse=operations[name];
			else if(operations.find("no_name")!=operations.end())
			{
				parse=operations["no_name"];
			}else
			{
				cerr<<"unable to evaluate with the given input"<<endl;
				return true;
			}

			Evaluator* ev=new Evaluator(parse,&operations);
			cerr<<"The value is "<<ev->getValue()<<endl;
		}break;
		default:
		{
			string equation=input;
			Equation_Parser* parse=new Equation_Parser(equation);
			bool success=parse->parse_now();
			if(!success)
			{
				cerr<<"parsing failed"<<endl;
			}else
				operations["no_name"]=parse;
		}break;
		case 5:
		{
			return false;
		}
	}

	return true;
}
