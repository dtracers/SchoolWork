/*
 * ExpressionTree.cpp
 *
 *  Created on: Feb 9, 2012
 *      Author: gigemjt
 */

#include "ExpressionTree.h"
#include "LogicHandler.h"
#include "OPERATIONS.cpp"
#include "DatabaseException.h"
#include<sstream>
#include <math.h>
#include<iostream>
#include "Date.h"
#include "Time.h"
#include "Database.h"

namespace LogicExpression {

/**
 * Default Constructor
 */
ExpressionTree::ExpressionTree() {
	// TODO Auto-generated constructor stub
	left = NULL;
	right = NULL;
}
/**
 * Sets the left to leftBranch
 * Sets the right to the rightBranch
 */
ExpressionTree::ExpressionTree(ExpressionTree* leftBranch,
		ExpressionTree* rightBranch) {
	left = leftBranch;
	right = rightBranch;
}

/**
 * Sets the value to V
 */
void ExpressionTree::setValue(string v) {
	value = v;
}

/**
 * Sends the Dabase for special commands like ANY and ALL
 */
void ExpressionTree::setDataBase(Database* db) {
	this->db = db;
	if (left != NULL)
		left->setDataBase(db);
	if (right != NULL)
		right->setDataBase(db);
}

/**
 * This will evaluate the tree
 * variables found in the tree will be replaced with replacements
 * it will return a float
 */
float ExpressionTree::evaluate(vector<string> variables,
		vector<string> replacements) {
	for (int k = 0; k < variables.size(); k++) {
		//	cout<<variables[k]<<" is replaced with "<<replacements[k]<<endl;
		replaceTemporaryValue(variables[k], replacements[k]);
	}
	stringstream stream(evaluate());
	float f;
	stream >> f;
	return f;
}

/**
 * This will evalute the tree
 * It uses type safety returns a string of the result
 */
string ExpressionTree::evaluate() {
	string num;

	if (!replaceable) {
		if (left == NULL || right == NULL) {
			throw DatabaseException(18,
					"Must have both left and right side to evaluate.");
		}
		string left_side = left->evaluate();
		string right_side = right->evaluate();

		string result;
		int type1 = valType(left_side); //0 is string
		//1 is float
		//2 is int
		//3 is date
		//4 is time
		int type2 = valType(right_side);
//		cout << "LEFT TYPE IS " << type1;
//		cout << " LEFT IS " << left_side << endl;
//		cout << "RIGHT TYPE IS " << type2;
//		cout << " RIGHT IS " << right_side << endl;
//		cout << "OPERATION IS" << value << endl;
		int intLeft;
		int intRight;
		float floatLeft;
		float floatRight;
		string stringLeft = left_side;
		string stringRight = right_side;
		Date dateLeft;
		Date dateRight;
		Time timeLeft;
		Time timeRight;
		stringstream leftStream(left_side);
		stringstream rightStream(right_side);
		switch (type1) {
		case 2:
			leftStream >> intLeft;
			break;
		case 1:
			leftStream >> floatLeft;
			break;
		case 3:
			leftStream >> dateLeft;
			break;
		case 4:
			leftStream >> timeLeft;
			break;
		}
		switch (type2) {
		case 2:
			rightStream >> intRight;
			break;
		case 1:
			rightStream >> floatRight;
			break;
		case 3:
			rightStream >> dateRight;
			break;
		case 4:
			rightStream >> timeRight;
			break;
		}
		//FIXX: Make sure type1 == type2, except for int and float
		Operations SWITCH = operation_map[value];
		switch (SWITCH) {
		//what she is doing
		case EQUAL: {
			bool tempResult;
			if (type1 == 0 && type2 == 0) {
				tempResult = (stringLeft == stringRight);
			} else if (type1 == 1 && type2 == 1) {
				tempResult = (floatLeft == floatRight);
			} else if (type1 == 1 && type2 == 2) {
				tempResult = (floatLeft == (float) intRight);
			} else if (type1 == 2 && type2 == 1) {
				tempResult = ((float) intLeft == floatRight);
			} else if (type1 == 2 && type2 == 2) {
				tempResult = (intLeft == intRight);
			} else if (type1 == 3 && type2 == 3) {
				tempResult = (dateLeft == dateRight);
			} else if (type1 == 4 && type2 == 4) {
				tempResult = (timeLeft == timeRight);
			} else {
				throw DatabaseException(
						18,
						intTypeToString(type1) + " and "
								+ intTypeToString(type2)
								+ " can not be compared using the == operator");
			}
			result = tempResult ? "1" : "0";
		}
			break;
		case NOT_EQUAL: {
			bool tempResult;
			if (type1 == 0 && type2 == 0) {
				tempResult = (stringLeft != stringRight);
			} else if (type1 == 1 && type2 == 1) {
				tempResult = (floatLeft != floatRight);
			} else if (type1 == 1 && type2 == 2) {
				tempResult = (floatLeft != (float) intRight);
			} else if (type1 == 2 && type2 == 1) {
				tempResult = ((float) intLeft != floatRight);
			} else if (type1 == 2 && type2 == 2) {
				tempResult = (intLeft != intRight);
			} else if (type1 == 3 && type2 == 3) {
				tempResult = (dateLeft != dateRight);
			} else if (type1 == 4 && type2 == 4) {
				tempResult = (timeLeft != timeRight);
			} else {
				throw DatabaseException(
						18,
						intTypeToString(type1) + " and "
								+ intTypeToString(type2)
								+ " can not be compared using the != operator");
			}
			result = tempResult ? "1" : "0";
		}
			break;
		case LTE: {
			bool tempResult;
			if (type1 == 0 && type2 == 0) {
				tempResult = (stringLeft <= stringRight);
			} else if (type1 == 1 && type2 == 1) {
				tempResult = (floatLeft <= floatRight);
			} else if (type1 == 1 && type2 == 2) {
				tempResult = (floatLeft <= (float) intRight);
			} else if (type1 == 2 && type2 == 1) {
				tempResult = ((float) intLeft <= floatRight);
			} else if (type1 == 2 && type2 == 2) {
				tempResult = (intLeft <= intRight);
			} else if (type1 == 3 && type2 == 3) {
				tempResult = (dateLeft <= dateRight);
			} else if (type1 == 4 && type2 == 4) {
				tempResult = (timeLeft <= timeRight);
			} else {
				throw DatabaseException(
						18,
						intTypeToString(type1) + " and "
								+ intTypeToString(type2)
								+ " can not be compared using the <= operator");
			}
			result = tempResult ? "1" : "0";
		}
			break;
		case GTE: {
			bool tempResult;
			if (type1 == 0 && type2 == 0) {
				tempResult = (stringLeft >= stringRight);
			} else if (type1 == 1 && type2 == 1) {
				tempResult = (floatLeft >= floatRight);
			} else if (type1 == 1 && type2 == 2) {
				tempResult = (floatLeft >= (float) intRight);
			} else if (type1 == 2 && type2 == 1) {
				tempResult = ((float) intLeft >= floatRight);
			} else if (type1 == 2 && type2 == 2) {
				tempResult = (intLeft >= intRight);
			} else if (type1 == 3 && type2 == 3) {
				tempResult = (dateLeft >= dateRight);
			} else if (type1 == 4 && type2 == 4) {
				tempResult = (timeLeft >= timeRight);
			} else {
				throw DatabaseException(
						18,
						intTypeToString(type1) + " and "
								+ intTypeToString(type2)
								+ " can not be compared using the >= operator");
			}
			result = tempResult ? "1" : "0";
		}
			break;
		case LT: {
			bool tempResult;
			if (type1 == 0 && type2 == 0) {
				tempResult = (stringLeft < stringRight);
			} else if (type1 == 1 && type2 == 1) {
				tempResult = (floatLeft < floatRight);
			} else if (type1 == 1 && type2 == 2) {
				tempResult = (floatLeft < (float) intRight);
			} else if (type1 == 2 && type2 == 1) {
				tempResult = ((float) intLeft < floatRight);
			} else if (type1 == 2 && type2 == 2) {
				tempResult = (intLeft < intRight);
			} else if (type1 == 3 && type2 == 3) {
				tempResult = (dateLeft < dateRight);
			} else if (type1 == 4 && type2 == 4) {
				tempResult = (timeLeft < timeRight);
			} else {
				throw DatabaseException(
						18,
						intTypeToString(type1) + " and "
								+ intTypeToString(type2)
								+ " can not be compared using the < operator");
			}
			result = tempResult ? "1" : "0";
		}
			break;
		case GT: {
			bool tempResult;
			if (type1 == 0 && type2 == 0) {
				tempResult = (stringLeft > stringRight);
			} else if (type1 == 1 && type2 == 1) {
				tempResult = (floatLeft > floatRight);
			} else if (type1 == 1 && type2 == 2) {
				tempResult = (floatLeft > (float) intRight);
			} else if (type1 == 2 && type2 == 1) {
				tempResult = ((float) intLeft > floatRight);
			} else if (type1 == 2 && type2 == 2) {
				tempResult = (intLeft > intRight);
			} else if (type1 == 3 && type2 == 3) {
				tempResult = (dateLeft > dateRight);
			} else if (type1 == 4 && type2 == 4) {
				tempResult = (timeLeft > timeRight);
			} else {
				throw DatabaseException(
						18,
						intTypeToString(type1) + " and "
								+ intTypeToString(type2)
								+ " can not be compared using the > operator");
			}
			result = tempResult ? "1" : "0";
		}
			break;

			//parse it into a 1 or 0 do operation store in result
		case AND: {
			if ((type1 == 2 && type2 == 2) && intLeft < 2 && intRight < 2
					&& intLeft >= 0 && intRight >= 0) {
				//the bitwise and operation will the same as the normal && operation on a bool
				result = ((intLeft & intRight) == 1) ? "1" : "0";
			} else {
				throw DatabaseException(
						18,
						intTypeToString(type1) + " and "
								+ intTypeToString(type2)
								+ " can not be compared using the && operator");
			}
		}
			break;

		case OR: {
			if ((type1 == 2 && type2 == 2) && intLeft < 2 && intRight < 2
					&& intLeft >= 0 && intRight >= 0) {
				//the bitwise or operation will the same as the normal || operation on a bool
				result = ((intLeft | intRight) == 1) ? "1" : "0";
			} else {
				throw DatabaseException(
						18,
						intTypeToString(type1) + " and "
								+ intTypeToString(type2)
								+ " can not be compared using the && operator");
			}
		}
			break;

			//parse it into a number do operation, store into result
		case EXP:
			if (type1 != 1 && type1 != 2) {
				throw DatabaseException(18,
						stringLeft + " must be a float or int type.");
			} else if (type2 != 1 && type2 != 2) {
				throw DatabaseException(18,
						stringRight + " must be a float or int type.");
			}

			float val;

			//Convert the first value to a float
			if (type2 == 1) {
				val = (float) intRight;
			} else {
				val = floatRight;
			}

			//Get the result depending on the left value
			if (type1 == 1) {
				result = (int) pow(intLeft, val);
			} else {
				result = pow(floatLeft, val);
			}
			break;
		case MULT:
			if (type1 != 1 && type1 != 2) {
				throw DatabaseException(18,
						stringLeft + " must be a float or int type.");
			} else if (type2 != 1 && type2 != 2) {
				throw DatabaseException(18,
						stringRight + " must be a float or int type.");
			}

			if (type1 == 1) {
				if (type2 == 1) {
					result = intLeft * intRight;
				} else {
					result = intLeft * floatRight;
				}
			} else {
				if (type2 == 1) {
					result = floatLeft * intRight;
				} else {
					result = floatLeft * floatRight;
				}
			}

			break;
		case DIVIDE:
			if (type1 != 1 && type1 != 2) {
				throw DatabaseException(18,
						stringLeft + " must be a float or int type.");
			} else if (type2 != 1 && type2 != 2) {
				throw DatabaseException(18,
						stringRight + " must be a float or int type.");
			}
			if (type1 == 1) {
				if (type2 == 1) {
					result = intLeft / intRight;
				} else {
					result = intLeft / floatRight;
				}
			} else {
				if (type2 == 1) {
					result = floatLeft / intRight;
				} else {
					result = floatLeft / floatRight;
				}
			}

			break;
		case PLUS:
			if (type1 != 1 && type1 != 2) {
				throw DatabaseException(18,
						stringLeft + " must be a float or int type.");
			} else if (type2 != 1 && type2 != 2) {
				throw DatabaseException(18,
						stringRight + " must be a float or int type.");
			}
			if (type1 == 1) {
				if (type2 == 1) {
					result = intLeft + intRight;
				} else {
					result = intLeft + floatRight;
				}
			} else {
				if (type2 == 1) {
					result = floatLeft + intRight;
				} else {
					result = floatLeft + floatRight;
				}
			}

			break;
		case MINUS:
			if (type1 != 1 && type1 != 2) {
				throw DatabaseException(18,
						stringLeft + " must be a float or int type.");
			} else if (type2 != 1 && type2 != 2) {
				throw DatabaseException(18,
						stringRight + " must be a float or int type.");
			}
			if (type1 == 1) {
				if (type2 == 1) {
					result = intLeft - intRight;
				} else {
					result = intLeft - floatRight;
				}
			} else {
				if (type2 == 1) {
					result = floatLeft - intRight;
				} else {
					result = floatLeft - floatRight;
				}
			}

			break;
		case ALL:
		case ANY: {
//			cout<<"ANY OR ALL"<<endl;
//			cout<<stringLeft<<endl;
//			cout<<stringRight<<endl;
			//stringLeft = table.col
			//stringRight = table_one_col
			Column * leftCol = NULL;
			try {
				leftCol = db->findColumn(stringLeft);
			} catch (DatabaseException e) {
//				cout<<"ignore exception"<<endl;
			}
			if (leftCol == NULL) {
				leftCol = new Column(valueType(stringLeft));
				leftCol->addRow(stringLeft);
			}
			string leftColType = leftCol->getColumnType();

			Table * rightTable = db->findTable(stringRight);
			if (rightTable == NULL) {
				throw DatabaseException(10, stringRight + " does not exist.");
			}
			Column * rightTableColumn = rightTable->findColumn(
					rightTable->columnNames()[0]);
			string rightTableColType = rightTableColumn->getColumnType();

			if (rightTable->columnCount() != 1) {
				throw DatabaseException(18,
						stringRight + " must have 1 column for ANY/ALL.");
			} else if (leftColType.compare(rightTableColType) != 0
					&& !((leftColType == "int" && rightTableColType == "float")
							|| (leftColType == "float"
									&& rightTableColType == "int"))) {
				throw DatabaseException(
						13,
						leftColType + " is not the same as "
								+ rightTableColType);
			}

			int funcType = -1;
			string op = "";
			switch (SWITCH) {
			case ANY:
				funcType = 1;
				op = value.substr(0, value.find("ANY"));
				break;
			case ALL:
				funcType = 2;
				op = value.substr(0, value.find("ALL"));
				break;
			}
			LogicHandler * temp = new LogicHandler("LEFT" + op + "RIGHT");
			temp->parse();
			vector<string> inserts;
			inserts.push_back("LEFT");
			inserts.push_back("RIGHT");
			ExpressionTree * tree = temp->getTree();

			for (int i = 0; i < leftCol->rowCount(); i++) {

				string leftInput = leftCol->getValueAtRowIndex(i);

//				cout<<"\n\nLEFT INPUT IS "<<leftInput<<endl;
//				cout<<"\n\nfollows "<<leftCol->printDataList()<<"index is "<<i<<endl;

				for (int j = 0; j < rightTableColumn->rowCount(); j++) {
					string rightInput = rightTableColumn->getValueAtRowIndex(j);
					vector<string> throwaway;
					throwaway.push_back(leftInput);
					throwaway.push_back(rightInput);
					bool eval = tree->isTrue(inserts, throwaway);

					if (funcType == 1 && eval) {
						return "1";
					} else if (funcType == 2 && !eval) {
						return "0";
					}
				}
			}

			result = (funcType == 1) ? "0" : "1";

		}
			break;
		case IN: //FIXX: Does not catch if the column types differ. Convert types
		{
			result = "0";

			if (db->countColumnsByTable(stringRight) != 1) {
				throw DatabaseException(18,
						stringRight + " does not have only 1 column.");
			}

			Table *theTable = db->findTable(stringRight);

			vector<string> column = theTable->columnNames();

			Column *theColumn = theTable->findColumn(column[0]);

			for (int i = 0; i < theColumn->rowCount(); i++) {
				if (stringLeft == theColumn->getValueAtRowIndex(i)) {
					result = "1";
					break;
				}
			}

		}
			break;
		case EXIST: {
			Table * table = db->findTable(stringRight);
			if (table == NULL) {
				result = "0";
			} else if (table->columnCount() >= 1) {
				result = "1";
			} else {
				result = "0";
			}
		}
			break;
		}
		num = result;
		//this is an operation
	} else {

		//this is not an operation!
		//it should be a number!
		string evaluate = value;
		if (TemporaryValue != "") {
			evaluate = TemporaryValue;
			TemporaryValue = "";
		}
		num = evaluate;
	}
//	cout << "RETURN (" << num << ")" << endl;
	return num;
}

/**
 *this will return a bool based on the result being 1 or 0
 */
bool ExpressionTree::isTrue(vector<string> variables,
		vector<string> replacements) {
	return evaluate(variables, replacements) == 1 ? true : false;
}

/**
 * This will replace the variables in the tree with the temp value
 */
void ExpressionTree::replaceTemporaryValue(string variable, string temp) {
	if (getValue() == variable)
		this->TemporaryValue = temp;

	if (left != NULL)
		left->replaceTemporaryValue(variable, temp);

	if (right != NULL)
		right->replaceTemporaryValue(variable, temp);
}

/**
 * This will replace the value on the left with the value on the right
 */
void ExpressionTree::replaceValue(string columnName, string variable) {
	if (getValue() == columnName)
		this->setValue(variable);

	if (left != NULL)
		left->replaceValue(columnName, variable);

	if (right != NULL)
		right->replaceValue(columnName, variable);
}

/**
 * This will replace the value of the variable with the tree
 */
void ExpressionTree::replaceValue(string variable, ExpressionTree* Tree) {
	if (left != NULL) {
		if (left->getValue() == variable)
			this->setLeft(Tree);
		else
			left->replaceValue(variable, Tree);
	}

	if (right != NULL) {
		if (right->getValue() == variable)
			this->setRight(Tree);
		else
			right->replaceValue(variable, Tree);
	}
}

/**
 * Returns the value
 */
string ExpressionTree::getValue() {
	return value;
}

/**
 * Returns if the current node is replaceable
 */
bool ExpressionTree::getReplaceable() {
	return replaceable;
}

/**
 * Sets whether the current node is replaceable
 */
void ExpressionTree::setReplaceable(bool r) {
	replaceable = r;
}

/**
 * Sets the left Node to l
 */
void ExpressionTree::setLeft(ExpressionTree* l) {
	if (l == NULL)
		printf("I love you");
	left = l;
}

/**
 * Sets the right Node to l
 */
void ExpressionTree::setRight(ExpressionTree* l) {
	if (l == NULL)
		printf("I love you too");
	right = l;
}

/**
 * Deconstructor deletes the rest of the tree
 */
ExpressionTree::~ExpressionTree() {
	if (left != NULL)
		delete left;
	if (right = NULL
	)
		delete right;
}

/**
 * Prints out the tree
 */
void ExpressionTree::toString() {
	if (left != NULL) {
		left->toString();
	}
	cout << getValue();
	if (right != NULL) {
		right->toString();
	}
}

} /* namespace LogicExpression */
