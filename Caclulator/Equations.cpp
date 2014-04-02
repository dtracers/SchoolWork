/*
 * Equations.cpp
 *
 *  Created on: Sep 22, 2010
 *      Author: gigemjt
 */

#include"Token.cpp"
using namespace std;

struct Tree
{
public:
	Tree left;
	Tree right;
	Token t;
	Tree(Token to)
	{
		t=to;
	}
};
