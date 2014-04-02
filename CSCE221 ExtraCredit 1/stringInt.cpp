/*
 * stringInt.cpp
 *
 *  Created on: Sep 15, 2011
 *      Author: gigemjt
 */

#include "stringInt.h"
#include <sstream>


StringInt::StringInt(int t)
{
	stringstream s;
	s<<t;
	string temp;
	s>>temp;
	StringInt::number=temp;
}
StringInt::StringInt(string temp)
{
	StringInt::number=temp;
}
