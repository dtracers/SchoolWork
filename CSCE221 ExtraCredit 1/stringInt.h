/*
 * stringInt.h
 *
 *  Created on: Sep 15, 2011
 *      Author: gigemjt
 */

#ifndef STRINGINT_H_
#define STRINGINT_H_
#include<iostream>
using namespace std;
class StringInt
{
	string number;
public:
	StringInt(int t);
	StringInt(double t);
	StringInt(string number);
	string get_num() const
	{
		return number;
	}
};

#endif /* STRINGINT_H_ */

