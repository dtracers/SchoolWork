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
class Database;
namespace LogicExpression {
using namespace std;
class ExpressionTree {
public:
	ExpressionTree();
	ExpressionTree(ExpressionTree* leftBranch, ExpressionTree* rightBranch);
	void setReplaceable(bool r);
	bool getReplaceable();
	void setValue(string v);
	void replaceTemporaryValue(string variable, string temp);
	void replaceValue(string coumnName, string variable);
	void replaceValue(string variable, ExpressionTree* Tree);
	string evaluate();
	float evaluate(vector<string> variables, vector<string> replacements);
	bool isTrue(vector<string> variables, vector<string> replacements);
	void setLeft(ExpressionTree* l);
	void setRight(ExpressionTree* r);
	void setDataBase(Database* db);
	string getValue();
	void toString();
	virtual ~ExpressionTree();
private:
	Database* db;
	ExpressionTree* left;
	ExpressionTree* right;
	string value;
	//this is a temporary value that is only stored until evaluate is called
	//then it is deleted
	string TemporaryValue;
	bool replaceable;
};

} /* namespace LogicExpression */
#endif /* EXPRESSIONTREE_H_ */
