/*
 * ExpressionTree.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: gigemjt
 */

#include "ExpressionTree.h"

namespace LogicExpression {

	ExpressionTree::ExpressionTree() {
		// TODO Auto-generated constructor stub

	}
	ExpressionTree::ExpressionTree(ExpressionTree* leftBranch,ExpressionTree* rightBranch)
	{
		left=leftBranch;
		right=rightBranch;
	}
	void ExpressionTree::setValue(string v)
	{
		value=v;
	}

	/**
	 * This will replace the value on the left with the value on the right
	 */
	void ExpressionTree::replaceValue(string columnName,string variable)
	{
		if(getValue()==columnName)
		{
			this->setValue(variable);
		}
		if(left!=NULL)
		{
			left->replaceValue(columnName,variable);
		}
		if(right!=NULL)
		{
			right->replaceValue(columnName,variable);
		}
	}
	void ExpressionTree::replaceValue(string variable,ExpressionTree* Tree)
	{
		if(left!=NULL)
		{
			if(left->getValue()==variable)
			{
				this->setLeft(Tree);
			}else
				left->replaceValue(variable,Tree);
		}
		if(right!=NULL)
		{
			if(right->getValue()==variable)
			{
				this->setRight(Tree);
			}else
				right->replaceValue(variable,Tree);
		}
	}
	int ExpressionTree::evaluate(vector<string> variables,vector<string> replacements)
	{
		return 0;
	}
	bool ExpressionTree::isTrue(vector<string> variables,vector<string> replacements)
	{
		return evaluate(variables,replacements)==1?true:false;
	}
	string ExpressionTree::getValue()
	{
		return value;
	}
	bool ExpressionTree::getReplaceable()
	{
		return replaceable;
	}
	void ExpressionTree::setReplaceable(bool r)
	{
		replaceable=r;
	}
	void ExpressionTree::setLeft(ExpressionTree* l)
	{
		if(l==NULL)
			printf("I love you");
		left=l;
	}
	void ExpressionTree::setRight(ExpressionTree* l)
	{
		if(l==NULL)
			printf("I love you too");
		right=l;
	}
	ExpressionTree::~ExpressionTree() {
		if(left!=NULL)
			delete left;
		if(right=NULL)
			delete right;
	}
	void ExpressionTree::toString()
	{
		if(getValue()!="")
			printf(getValue().c_str());
		if(left!=NULL)
			left->toString();
		if(right!=NULL)
			right->toString();
	}

} /* namespace LogicExpression */
