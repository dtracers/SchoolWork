/*
 * LogicHandler.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: gigemjt
 */

#include "LogicHandler.h"
namespace LogicExpression {
	LogicHandler::LogicHandler(string g) {
		loadArray();
		parseString=g;
		// TODO Auto-generated constructor stub

	}
	void LogicHandler::parse()
	{
		long int value=getHighestOperation(parseString);
		if(value==-1)
		{
			cout<<"value is negative 1 "<<parseString<<endl;
			ExpressionTree* t=new ExpressionTree();
			t->setValue(parseString);
			t->setReplaceable(true);
			tree=t;
			return;
		}
		int type=((value)>>OPERATION_SHIFT)&MAX_OPERATION_COUNT;//this will get the type
				//int size=(value>>20);
		int position=(value&MAX_POSITION);//this will get the position
	//	cout<<"my type is !"<<type;
		switch(type)
		{
			case 0:// "("
			{
				cout<<"going down!!!"<<parseString<<endl;
				string temp=extractParenthesis(parseString,position);
				string inside="";
				for(int k=0;k<parenthDeepness;k++)
				{
					inside+="#";
				}
				parenthDeepness++;
				string around=parseString.substr(0,parenthStart)
						+inside
						+parseString.substr(parenthEnd+1,parenthEnd+1-parseString.length());
				cout<<"AROUND:: "<<around<<endl;
				cout<<"INSIDE:: "<<temp<<endl;
				LogicHandler below(temp);
				below.parse();
				LogicHandler above(around);
				above.parse();
				tree=above.getTree();
				ExpressionTree* tempTree=below.getTree();
				tree->replaceValue(inside,tempTree);
			}break;
			default:
			{
				value=getLowestOperation(parseString);
				if(value==-1)
				{
					cerr<<"highest and lowest returned different items?"<<endl;
					return;
				}
				int size=(value>>SIZE_SHIFT);
				type=((value)>>OPERATION_SHIFT)&MAX_OPERATION_COUNT;//this will get the type
				position=value&MAX_POSITION;//this will get the position
				ExpressionTree* t=new ExpressionTree();
				t->setValue(parseString.substr(position,size));
				t->setReplaceable(false);
				tree=t;
				string left=parseString.substr(0,position);
				string right=parseString.substr(position+size,parseString.length()-position);
				LogicHandler leftParser(left);
				leftParser.parse();
				LogicHandler rightParser(right);
				rightParser.parse();
				tree->setLeft(leftParser.getTree());
				tree->setRight(rightParser.getTree());
				return;
			}
		}
	}
	ExpressionTree* LogicHandler::getTree()
	{
		return tree;
	}
	/*
	 * This will get the string index
	 * The longest string the will be allowed is 1<<15
	 * or 2^15
	 * or 32767 which is long enough
	 */
	long int LogicHandler::getHighestOperation(string g)
	{
		int pos=0;
		long int index=-1;
		int size=0;
		for(int k=0;k<array.size();k++)
		{
			pos=g.find(array[k]);
			if(pos>=0)
			{
			//	cout<<"I have found "<<array[k]<<" at "<<index<<endl;
				size=array[k].size();
				index=k;
				//
				break;
			}
		}
		if(index==-1)
			return -1;
		return ((index&MAX_OPERATION_COUNT)<<OPERATION_SHIFT)
				+(pos&MAX_POSITION)
				+(size<<SIZE_SHIFT);//max value is 24<<15
				//32767 this will get the first value!!
	}
	long int LogicHandler::getLowestOperation(string g)
	{
		int pos=0;
		long int index=-1;
		int size=0;
		for(int k=array.size()-1;k>=0;k--)
		{
			pos=g.find(array[k]);
			if(pos>=0)
			{
				size=array[k].size();
				index=k;
			//	cout<<"I have found "<<array[k]<<" at "<<index<<endl;
			//	string new_string=extractParenthesis(g,index);
				break;
			}
		}
		if(index==-1)
			return -1;
		return ((index&MAX_OPERATION_COUNT)<<OPERATION_SHIFT)
				+(pos&MAX_POSITION)
				+(size<<SIZE_SHIFT);//max value is 24<<15
				//32767 this will get the first value!!
	}
	string LogicHandler::extractParenthesis(string g,int index)
	{
		int count=1;
		int index2=index+1;
		while(index2<g.length()&&count>0)
		{
			char character=g[index2];
			if(character=='(')
				count++;
			if(character==')')
				count--;
			index2++;
		}
		if(count>0)
			throw DatabaseException(50, g+" This is missing at least one \")\" ");
		parenthStart=index;
		parenthEnd=index2-1;
		return g.substr(index+1,(index2-1)-(index+1));
	}

	/**
	 * This will load all the arrays
	 */
	void LogicHandler::loadArray()
	{
		static bool arrayPush;
		if(!arrayPush)
		{
			parenthDeepness=1;
			array.push_back("(");
			array.push_back("<=");
			array.push_back(">=");
			array.push_back("!=");
			array.push_back("<");
			array.push_back(">");
			array.push_back("=");
			array.push_back("!");
			array.push_back("AND");
			array.push_back("OR");
			array.push_back("NOR");
			array.push_back("XOR");
			array.push_back("XNOR");
			array.push_back("NAND");
			array.push_back("ANY");
			array.push_back("ALL");
			array.push_back("IN");
			array.push_back("EXIST");
			array.push_back("^");
			array.push_back("*");
			array.push_back("/");
			array.push_back("+");
			array.push_back("-");
			arrayPush=true;
		}
	}
	LogicHandler::~LogicHandler() {
		//array.~vector();
		// TODO Auto-generated destructor stub
	}
	void LogicHandler::clear()
	{
		parenthDeepness=1;
	}
}
