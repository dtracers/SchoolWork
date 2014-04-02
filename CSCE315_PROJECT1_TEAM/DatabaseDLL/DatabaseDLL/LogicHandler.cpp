/*
 * LogicHandler.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: gigemjt
 */

#include "LogicHandler.h"
#include "OPERATIONS.cpp"
#include"ExpressionTree.h"
namespace LogicExpression {
LogicHandler::LogicHandler(string g) {
	loadArray();
	parseString = g;
//	cout<<"TREE PARSING "<<g<<endl;
}

/**
 * This will parse it
 * it gets the highest operation first
 * if it is a ( then it will parse the inside of that and the outside of that
 * otherwise
 * it gets the lowest operation then it will parse it  separarting it in half and then parsing it
 */
void LogicHandler::parse() {
	long int value = getHighestOperation(parseString);
	if (value == -1) {
		//	cout<<"value is negative 1 "<<parseString<<endl;
		ExpressionTree* t = new ExpressionTree();
		stringstream stream(parseString);
		string temp;
		stream >> temp;
		t->setValue(temp);
		t->setReplaceable(true);
		tree = t;
		return;
	}
	int type = ((value) >> OPERATION_SHIFT) & MAX_OPERATION_COUNT; //this will get the type
	int position = (value & MAX_POSITION); //this will get the position
	switch (type) {
	case 0: // "("
	{
		//	cout<<"going down!!!"<<parseString<<endl;
		string temp = extractParenthesis(parseString, position);
		string inside = "";
		for (int k = 0; k < parenthDeepness + 1; k++) {
			inside += "#";
		}
		parenthDeepness++;
		string around = parseString.substr(0, parenthStart) + inside
				+ parseString.substr(parenthEnd + 1,
						parenthEnd + 1 - parseString.length());
		//	cout<<"AROUND:: "<<around<<endl;
		//	cout<<"INSIDE:: "<<temp<<endl;
		LogicHandler below(temp);
		below.parse();
		ExpressionTree* tempTree = below.getTree();
		LogicHandler above(around);
		stringstream str(around);
		string onlyParenth;
		str>>onlyParenth;
		if(onlyParenth!=inside)
		{
			above.parse();
			tree = above.getTree();
			tree->replaceValue(inside, tempTree);
		}else
		{
			tree=tempTree;
		}

	}break;
	case 1: // "["
	{
		//	cout<<"going down!!!"<<parseString<<endl;
		string temp = extractBracket(parseString, position);
		string inside = "";
		for (int k = 0; k < parenthDeepness + 1; k++) {
			inside += "#";
		}
		parenthDeepness++;
		string around = parseString.substr(0, parenthStart) + inside
				+ parseString.substr(parenthEnd + 1,
						parenthEnd + 1 - parseString.length());
		//	cout<<"AROUND:: "<<around<<endl;
		//	cout<<"INSIDE:: "<<temp<<endl;
		LogicHandler above(around);
		above.parse();
		tree = above.getTree();
		tree->replaceValue(inside, temp);
	}
		break;
	default: {
		value = getLowestOperation(parseString);
		if (value == -1) {
			cerr << "highest and lowest returned different items?" << endl;
			return;
		}
		int size = (value >> SIZE_SHIFT);
		type = ((value) >> OPERATION_SHIFT) & MAX_OPERATION_COUNT; //this will get the type
		position = value & MAX_POSITION; //this will get the position
		ExpressionTree* t = new ExpressionTree();
		string value=parseString.substr(position, size);
	//	cout<<"OPERATION IS "<<value<<endl;
		t->setValue(value);
		t->setReplaceable(false);
		tree = t;
		string left = parseString.substr(0, position);
		string right = parseString.substr(position + size,
				parseString.length() - position);
	//	cout<<"LEFT IS "<<left<<endl;
	//	cout<<"RIGHT IS "<<right<<endl;
		LogicHandler leftParser(left);
		leftParser.parse();
		LogicHandler rightParser(right);
		rightParser.parse();
		tree->setLeft(leftParser.getTree());
		tree->setRight(rightParser.getTree());
		//tree->toString();
		//	cout << endl;
		//	cout<<"I am returning"<<endl;
		return;
	}
	}
}
ExpressionTree* LogicHandler::getTree() {
	return tree;
}
/*
 * This will get the string index
 * The longest string the will be allowed is 1<<15
 * or 2^15
 * or 32767 which is long enough
 */
long int LogicHandler::getHighestOperation(string g) {
	int pos = 0;
	long int index = -1;
	int size = 0;
	for (int k = 0; k < operation_array.size(); k++) {
		pos = g.find(operation_array[k]);
		if (pos >= 0) {
			//	cout<<"I have found "<<operation_array[k]<<" at "<<index<<endl;
			size = operation_array[k].size();
			index = k;
			//
			break;
		}
	}
	if (index == -1)
		return -1;
	return ((index & MAX_OPERATION_COUNT) << OPERATION_SHIFT)
			+ (pos & MAX_POSITION) + (size << SIZE_SHIFT); //max value is 24<<15
	//32767 this will get the first value!!
}
long int LogicHandler::getLowestOperation(string g) {
	int pos = 0;
	long int index = -1;
	int size = 0;
	for (int k = operation_array.size() - 1; k >= 0; k--) {
		pos = g.find(operation_array[k]);
		if (pos >= 0) {
			size = operation_array[k].size();
			index = k;
			//	cout<<"I have found "<<operation_array[k]<<" at "<<index<<endl;
			//	string new_string=extractParenthesis(g,index);
			break;
		}
	}
	if (index == -1)
		return -1;
	return ((index & MAX_OPERATION_COUNT) << OPERATION_SHIFT)
			+ (pos & MAX_POSITION) + (size << SIZE_SHIFT); //max value is 24<<15
	//32767 this will get the first value!!
}
string LogicHandler::extractParenthesis(string g, int index) {
	int count = 1;
	int index2 = index + 1;
	while (index2 < g.length() && count > 0) {
		char character = g[index2];
		if (character == '(')
			count++;
		if (character == ')')
			count--;
		index2++;
	}
	if (count > 0)
		throw DatabaseException(50, g + " This is missing at least one \")\" ");
	parenthStart = index;
	parenthEnd = index2 - 1;
	return g.substr(index + 1, (index2 - 1) - (index + 1));
}
string LogicHandler::extractBracket(string g, int index) {
	int count = 1;
	int index2 = index + 1;
	while (index2 < g.length() && count > 0) {
		char character = g[index2];
		if (character == '[')
			count++;
		if (character == ']')
			count--;
		index2++;
	}
	if (count > 0)
		throw DatabaseException(50, g + " This is missing at least one \")\" ");
	parenthStart = index;
	parenthEnd = index2 - 1;
	return g.substr(index + 1, (index2 - 1) - (index + 1));
}

LogicHandler::~LogicHandler() {
	//operation_array.~vector();
	// TODO Auto-generated destructor stub
}
void LogicHandler::clear() {
	parenthDeepness = 0;
}
}
