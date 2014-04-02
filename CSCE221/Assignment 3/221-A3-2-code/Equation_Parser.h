#ifndef EQUATION_PARSER_H
#define EQUATION_PARSER_H
using namespace std;
#include "Element.h"
#include "LinkedStack.h"
#include "RuntimeException.h"
#include "Utility.h"
#include <map>

class Equation_Parser {
private:
	LinkedStack<Element>* function;
	int error;
	int pop_state;
  //it is in the order of the symbol on top followed by the left one then the right one
  //ex:
  /*
  Index
     	0 | 1 | 2 | 3 | 4
Element
     	2   4   *   3   +
Function in infix
 	 	2*4+3
Function in post fix
		2   4   *   3   +
Function in prefix
        +   *   2   4   3
   */
	int parse(string s,int bottom,int high,Element* left,LinkedStack<Element>* list,int layer)
	{
		//s has no spaces in it
		//if it is a number or variable just add it to the stack
		//otherwise continue going right and look for the next symbol if it is a higher priority
		//then start after the symbol and continue.
		//luckily the only thing between symbols is a number so it should be read anyways
		//if it is the same add all together and keep going
		//if it is lower
		//then keep going unless the previous was of higher value
		//??
		//profit
		if(error==1)
			return high+1;
		bool looping=true;
		int k=bottom;//current index
		Element* second_left=NULL;
		Element* operation;
		string num;
		int first_imp=0;
		Element* special_operation=NULL;
		while(looping)
		{
			cerr<<"index "<<k<<" s[k] "<<s[k]<<endl;
			cerr<<" List: "<<*list<<endl;
			int imp=importance((s[k]));
			if(imp<0)
			{
				second_left=new Element(num);
				num="";
				if(left!=NULL&&!left->is_place_holder())
					list->push(*left);
				list->push(*second_left);
				if(operation!=NULL&&!operation->is_place_holder())
				{
					list->push(*operation);
				}
				return -(k+1);
			}
			if(imp==5)//'\' this is for special ones... they have to have a parenthesis around terms
			{
				k++;
				string num2="";
				while(k<high&&s[k]!='(')
				{
					num2+=s[k];
					cerr<<"index "<<k<<" s[k] "<<s[k]<<endl;
					k++;
				};
				special_operation=new Element(num2,true);
				imp=4;
				while(s[k]!='(')
				{
					k++;
					cerr<<"index "<<k<<" s[k] "<<s[k]<<endl;
				}
			}
			if(imp==4)//'('
			{
				if(left!=NULL&&!left->is_place_holder())
					list->push(*left);
				int index=parse(s,k+1,high,NULL,list,0);
				if(index<0)
					index=-index;
				if(index>=high)
				{
					if(special_operation!=NULL)
						list->push(*special_operation);
					if(operation!=NULL)
						list->push(*operation);
					return index;
				}else if(s[index]==')')
				{
					if(special_operation!=NULL)
						list->push(*special_operation);
					if(operation!=NULL)
						list->push(*operation);
					return -(index+1);
				}
				if(special_operation!=NULL)
					list->push(*special_operation);
				if(importance(s[index])>first_imp)
				{
					k=index;
					index=parse(s,k,high,new Element(),list,layer+1);
					if(index<0)
						return index;
					k=index;
				}
				if(operation!=NULL)
					list->push(*operation);

				k=index;
				if(k>=high)
					return k;
				index=parse(s,k,high,new Element(),list,layer);
				if(index<0)
					return index;
				k=index-1;
				return k;
			}else
			{
				if(left==NULL||first_imp==0)
				{
					if(imp==0)
						num+=s[k];
					else
					{
						if(left==NULL)
							left=new Element(num);
						first_imp=imp;
						operation=new Element(s[k]);
						num="";
					}
				}else
				{
					if(imp==0)
						num+=s[k];
					else
					{
						if(second_left==NULL)
						{
							second_left=new Element(num);
							num="";
						}
						if(imp>first_imp||(imp==first_imp&&imp==3))//example is + then *  also ^ then ^ is under this catagory
						{
							if(!left->is_place_holder())
							list->push(*left);
							int index=parse(s,k,high,second_left,list,layer+1);
							list->push(*operation);
							if(index<0)
								return index;
							k=index;
							int temp=k;
							if(temp<=high&&imp==3&&layer>0)
							{
								temp-=1;
								int imp2=importance(s[temp]);
								while(imp2==0)
								{
									imp2=importance(s[temp]);
									temp++;
								}
								if(imp2<imp)
								{
									return index;
								}
							}
							if(k>=high)
								return k;
							left=new Element();
							index=parse(s,k,high,left,list,layer);
							if(index<0)
								return index;
							k=index-1;
							return k;
						}else if(imp<first_imp)// if it is * then +
						{
							if(!left->is_place_holder())
								list->push(*left);
							list->push(*second_left);
							list->push(*operation);
							if(layer>0&&(first_imp-imp)<=layer)
								return k;
							operation=new Element(s[k]);
							int index=parse(s,k,high,new Element(),list,layer);//this should add this to the linked list first
							if(index<0)
								return index;
							k=index-1;
						}else if(imp==first_imp)//if it is + then +
						{
							if(!left->is_place_holder())
								list->push(*left);
							list->push(*second_left);
							list->push(*operation);
							operation=new Element(s[k]);
							int index=parse(s,k,high,new Element(),list,layer);//this should add this to the linked list first
							int temp=index;
							if(index<0)
								return index;
							if(temp<=high)
							{
								temp-=1;
								int imp2=importance(s[temp]);
								while(imp2==0)
								{
									imp2=importance(s[temp]);
									temp++;
								}
								if(imp2<imp)
								{
									return index;
								}
							}
							k=index-1;
						}
					}
				}
			}
			k++;
			looping=!(k>=high);
		}
		if(num!="")
		{
			second_left=new Element(num);
			if(left!=NULL&&!left->is_place_holder())
				list->push(*left);
			list->push(*second_left);
			if(operation!=NULL&&!operation->is_place_holder())
			list->push(*operation);
		}
		return high;
	}
  /* declare utility functions */
	int importance(char& c)
	{
		switch(c)
		{
			case '+':
			case '-':return 1;
			case '*':
			case '/':return 2;
			case '^':return 3;
			case '(':return 4;
			case '\\':return 5;
			case ')':return -1;
		}
		return 0;
	}
public:
string parsing;
// constructor
	Equation_Parser(string s)
	{
		parsing=s;
	}
	bool parse_now()
	{
		LinkedStack<Element>* list=new LinkedStack<Element>();
		parsing=preparser(parsing);
		int length=parse(parsing,0,parsing.length(),NULL,list,0);
		if(error==1)
		{
			cerr<<"The input was not syntactically correct"<<endl;
			function=NULL;
			return false;
		}else
		{
			cerr<<"The input in post fix is: "<<*list<<endl;
			function=list;
			return true;
		}
	}
	string preparser(string g)
	{
		pop_state=-1;
		cerr<<"pre Equation_Parser "<<g<<endl;
		string g_out="";
		int prev_imp=-3;
		int current_imp=-3;
		int parenthcount=0;
		for(int k=0;k<g.size();k++)
		{
			prev_imp=current_imp;
			if(g[k]==' ')
			{
			}else
			{
				current_imp=importance(g[k]);
				bool two_symbols=((prev_imp>0&&current_imp>0));
				if((two_symbols||k==0)&&g[k]=='-')
				{
					if(g[k]=='-')
					{
						g_out+="(0";
						g_out+=g[k];
					}
					k+=1;
					int index=k;
					if(g[k]=='(')
					{
						parenthcount+=1;
						g_out+=g[k];
						k+=1;
					}
					while(k<g.size()&&(importance(g[k])==0||parenthcount>0))
					{
						if(g[k]=='(')
							parenthcount++;
						else if(g[k]==')')
							parenthcount--;
						g_out+=g[k];
						k++;
					}
					if(parenthcount>0)
						error=1;
					g_out+=")";
					k=index;
				}else if(two_symbols&&g[k]!='-')
				{
					error=1;
					return "";
				}
				else
				{
					g_out+=g[k];
				}
			}
		}
		cerr<<"done with pre-parsing "<<g_out<<"\n\n"<<endl;
		return g_out;
	}
  // operations
	void printInfix() { }
	void printPostfix() { }
	LinkedStack<Element>* getList()
	{
		return function;
	}
};

#endif
