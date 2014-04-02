/*
 * Element.h
 *
 *  Created on: Oct 10, 2011
 *      Author: gigemjt
 */
#ifndef ELEMENT_H_
#define ELEMENT_H_
#include <iostream>
#include <sstream>
#include <string>
#include "LinkedStack.h"
using namespace std;
class Element
{
private:
	string element;
	char operation;
	string cool_op;
	bool place_holder;
	LinkedStack<Element>* equations;
public:
	string to_string() const
	{
		if(is_place_holder())
			return "PLACE_HOLDER";
		if(is_cool_operand())
			return get_cool_operand();
		if(is_operand())
		{
			string g="";
			char x=get_operand();
			g+=x;
			return g;
		}
		if(is_equation())
		{
			stringstream s;
			s<<*get_equation();
			string g;
			s>>g;
			return g;
		}
		return get_value();
	}
	Element(string& g)
	{
		set_everything_null();
		string* temp=&g;
		char &t=(*temp)[0];
		if(t=='^'||t=='*'||t=='+'||t=='/')
		{
			operation=t;
			element="";
		}else
		{
			string g2="";
			for(int k=0;k<temp->size();k++)
			{
				char monkey=(*temp)[k];
				if(monkey!=' ')
				{
					g2+=monkey;
				}
			}
			element=g2;
		}
	}
	Element(string& g,bool f)
	{
		set_everything_null();
		string* temp=&g;
		cool_op=*temp;
	}
	Element(char& g)
	{
		set_everything_null();
		operation=g;
	//	cerr<<"OPERATIONAL MONEKY "<<operation;
	}
	Element()
	{
		set_everything_null();
		place_holder=true;
	}
	Element(LinkedStack<Element>* equation)
	{
		set_everything_null();
		equations=equation;
	}
	void set_everything_null()
	{
		cool_op="";
		equations=NULL;
		element="";
		place_holder=false;
	}
	LinkedStack<Element>* get_equation() const
	{
		return equations;
	}
	char get_operand() const
	{
		return operation;
	}
	string get_cool_operand() const
	{
		return cool_op;
	}
	string get_value() const
	{
		return element;
	}
	bool is_place_holder() const
	{
		return place_holder;
	}
	friend ostream & operator<< (ostream& out, const Element& ll)
	{
		out<<ll.to_string();
		return out;
	}
	bool is_operand() const
	{
		return element==""&&!is_place_holder();
	}
	bool is_cool_operand() const
	{
	//	cout<<element<<(element=="")<<endl;
		return is_operand()&&cool_op!="";
	}
	bool is_equation() const
	{
		return !is_place_holder()&&equations!=NULL;
	}
};
#endif /* ELEMENT_H_ */
