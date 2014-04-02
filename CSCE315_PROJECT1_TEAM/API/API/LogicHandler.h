/*
 * LogicHandler.h
 *
 *  Created on: Feb 9, 2012
 *      Author: gigemjt
 */

#ifndef LOGICHANDLER_H_
#define LOGICHANDLER_H_
#include"ExpressionTree.h"
#include"DatabaseException.h"
#include<vector>
#include<map>

#define SIZE_SHIFT 20
#define MAX_POSITION 32767
#define MAX_OPERATION_COUNT 31
#define OPERATION_SHIFT 15

namespace LogicExpression {

static vector<string> array;
static int parenthDeepness;

	class LogicHandler {
	public:
		LogicHandler(string g);
		void parse();
		ExpressionTree* getTree();
		virtual ~LogicHandler();
	private:
		int parenthStart;
		int parenthEnd;
		string parseString;
		ExpressionTree* tree;
		long int getHighestOperation(string g);
		long int getLowestOperation(string g);
		void loadArray();
		void clear();
		string extractParenthesis(string g,int index);
	};
}
#endif /* LOGICHANDLER_H_ */
