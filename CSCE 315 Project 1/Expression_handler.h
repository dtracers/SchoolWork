/*
 * Expression_handler.h
 *
 *  Created on: Feb 1, 2012
 *      Author: gigemjt
 */

#ifndef EXPRESSION_HANDLER_H_
#define EXPRESSION_HANDLER_H_
#include<string>
using namespace std;
/**
 * This is the expression handler which will handle all numerical and logical expressions
 * it will be like my expression tree from java
 * it will have variables that can then be inputed
 * I will combine it with logic so that it can handle AND and OR
 * TODO: make this!
 * TODO:it needs to be done by the end of tomorrow
 */
class Expression_handler {
public:
	Expression_handler(string expression);
	virtual ~Expression_handler();
};

#endif /* EXPRESSION_HANDLER_H_ */
