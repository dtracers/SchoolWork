/*
 * Token.cpp
 *
 *  Created on: Sep 22, 2010
 *      Author: gigemjt
 */
using namespace std;
struct Token
{
	char kind;
	double value;
	Token(char ch):kind(ch){}
	Token(char ch,double value):kind(ch),value(value){}
	Token():kind(0),value(0){}
};

