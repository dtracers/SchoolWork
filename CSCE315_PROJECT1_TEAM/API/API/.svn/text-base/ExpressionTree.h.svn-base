/*
 * ExpressionTree.h
 *
 *  Created on: Feb 9, 2012
 *      Author: gigemjt
 */

#ifndef EXPRESSIONTREE_H_
#define EXPRESSIONTREE_H_
#include<string>
#include <vector>
namespace LogicExpression {
	using namespace std;
	class ExpressionTree {
	public:
		ExpressionTree* left;
		ExpressionTree* right;
		string value;
		bool replaceable;
		ExpressionTree();
		ExpressionTree(ExpressionTree* leftBranch,ExpressionTree* rightBranch);
		void setReplaceable(bool r);
		bool getReplaceable();
		void setValue(string v);
		void replaceValue(string coumnName,string variable);
		void replaceValue(string variable,ExpressionTree* Tree);
		int evaluate(vector<string> variables,vector<string> replacements);
		bool isTrue(vector<string> variables,vector<string> replacements);
		void setLeft(ExpressionTree* l);
		void setRight(ExpressionTree* r);
		string getValue();
		void toString();
		virtual ~ExpressionTree();
	};

} /* namespace LogicExpression */
#endif /* EXPRESSIONTREE_H_ */
