/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The class that deals with values and the operations
*/

#include<map>
#include<vector>
#include<string>
#include<sstream>
#include"Time.h"
#include"Date.h"
#include "global_parsing_methods.h"
#ifndef OPERATIONS_CPP_
#define OPERATIONS_CPP_
using namespace std;
namespace LogicExpression {

enum Operations {
	LTE, GTE, LT, GT, NOT_EQUAL, EQUAL, //equality
	AND,
	OR,
	NOR,
	XOR,
	XNOR,
	NAND, //boolean
	ANY,
	ALL,
	IN,
	EXIST, //other
	EXP,
	MULT,
	DIVIDE,
	PLUS,
	MINUS
//math
};
//	vector<string> loadArray();
//	map<string,Operations> loadMap();

/**
 * This will load all the arrays
 */
static vector<string> loadArray() {
	vector<string> array;

	array.push_back("(");
	array.push_back("[");
	array.push_back("<=");
	array.push_back(">=");
	array.push_back("!=");
	array.push_back("=");
	array.push_back("<");
	array.push_back(">");
	array.push_back("<=");
	array.push_back(">=");
	array.push_back("<=");
	array.push_back("!");
	array.push_back("<="); //so that this is will choose these first from lower or higher
	array.push_back(">="); //it wont affect anything else
	array.push_back("!=");
	array.push_back("&&");
	array.push_back("||");
	array.push_back("AND");
	array.push_back("OR");
//	array.push_back("NOR");
//	array.push_back("XOR");
//	array.push_back("XNOR");
//	array.push_back("NAND");
	array.push_back("ANY");
	array.push_back("ALL");
	array.push_back("IN");
	array.push_back("EXIST");
	array.push_back(">=ANY");
	array.push_back("!=ANY");
	array.push_back("<ANY");
	array.push_back(">ANY");
	array.push_back("<=ANY");
	array.push_back(">=ANY");
	array.push_back("=ANY");
	array.push_back(">=ALL");
	array.push_back("!=ALL");
	array.push_back("<ALL");
	array.push_back(">ALL");
	array.push_back("<=ALL");
	array.push_back(">=ALL");
	array.push_back("=ALL");
	array.push_back("^");
	array.push_back("*");
	array.push_back("/");
	array.push_back("+");
	array.push_back("-");

	return array;
}

static map<string, Operations> loadMap() {
	map<string, Operations> array;
	array["<="] = LTE;
	array[">="] = GTE;
	array["!="] = NOT_EQUAL;
	array["<"] = LT;
	array[">"] = GT;
	array["="] = EQUAL;
	array["&&"] = AND;
	array["||"] = OR;
	array["AND"] = AND;
	array[">=ANY"] = ANY;
	array["!=ANY"] = ANY;
	array["<ANY"] = ANY;
	array[">ANY"] = ANY;
	array["<=ANY"] = ANY;
	array[">=ANY"] = ANY;
	array["=ANY"] = ANY;
	array[">=ALL"] = ALL;
	array["!=ALL"] = ALL;
	array["<ALL"] = ALL;
	array[">ALL"] = ALL;
	array["<=ALL"] = ALL;
	array[">=ALL"] = ALL;
	array["=ALL"] = ALL;
	array["OR"] = OR;
	array["NOR"] = NOR;
	array["XOR"] = XOR;
	array["XNOR"] = XNOR;
	array["NAND"] = NAND;
	array["ANY"] = ANY;
	array["ALL"] = ALL;
	array["IN"] = IN;
	array["EXIST"] = EXIST;
	array["^"] = EXP;
	array["*"] = MULT;
	array["/"] = DIVIDE;
	array["+"] = PLUS;
	array["-"] = MINUS;
	return array;
}

static map<string, Operations> operation_map = loadMap();
static vector<string> operation_array = loadArray();

/**
 * THis will return the type based on the value
 * 0 is string
 * 1 is int
 * 2 is float
 * 3 is date
 * 4 is time
 */
static int valType(string val) {
	int type = 4;
	if (type == 4) {
		stringstream typecast(val);
		Time timeVal;
		typecast >> timeVal;
		stringstream back;
		back << timeVal;
		string temp;
		back >> temp;
		
		//atoi returns 0 if not successful

		if (temp != val && globalParse::get_separate_statments(temp, ":").size() != 2) {
			//dont throw an error
			type -= 1;
			//	throw DatabaseException(41, val + " is not a valid time. Accepted format is HH:MM:SS.");
		}
	}
	if (type == 3) {

		stringstream typecast(val);
		Date dateVal;
		typecast >> dateVal;
		stringstream back;
		back << dateVal;
		string temp;
		back >> temp;
		if (temp != val && globalParse::get_separate_statments(temp, "/").size() != 2) {
			type -= 1;
			//	throw DatabaseException(40, val + " is not a valid date. Accepted format is YYYY/MM/DD.");
		}

	}
	if (type == 2) {
		//this should do an int first

		stringstream typecast(val);
		int intVal = 0;
		typecast >> intVal;
		stringstream back;
		back << intVal;
		string temp;
		back >> temp;

		//atoi returns 0 if not successful

		if (temp != val) {
			//	cout << "I AM PRINTING AS AN INT!" << temp << " " << val << endl;
			type -= 1;
			//throw DatabaseException(33, val + " not a valid integer.");
		} else
			return 2;
	}
	if (type == 1) {
		stringstream typecast(val);
		float floatVal = 0;
		typecast >> floatVal;
		stringstream back;
		back << floatVal;
		string temp;
		back >> temp;

		//atoi returns 0 if not successful

		//for cases were the float value is 10.00
		if (temp != val) {
			stringstream test2(temp);
			//case for an int
			int other;
			test2 >> other;
			if (other != floatVal || val.find(".0") == -1) {
				type -= 1;
			} else
				return 1;
			//	throw DatabaseException(34, val + " not a valid float.");
		} else
			return 1;
	}

	return type;
}
static string valueType(string val) {
	int type = 4;
	if (type == 4) {
		stringstream typecast(val);
		Time timeVal;
		typecast >> timeVal;
		stringstream back;
		back << timeVal;
		string temp;
		back >> temp;

		//atoi returns 0 if not successful

		if (temp != val) {
			//dont throw an error
			type -= 1;
			//	throw DatabaseException(41, val + " is not a valid time. Accepted format is HH:MM:SS.");
		} else {
			return "time";
		}
	}
	if (type == 3) {

		stringstream typecast(val);
		Date dateVal;
		typecast >> dateVal;
		stringstream back;
		back << dateVal;
		string temp;
		back >> temp;
		if (temp != val) {
			type -= 1;
			//	throw DatabaseException(40, val + " is not a valid date. Accepted format is YYYY/MM/DD.");
		} else {
			return "date";
		}

	}
	if (type == 2) {
		//this should do an int first

		stringstream typecast(val);
		int intVal = 0;
		typecast >> intVal;
		stringstream back;
		back << intVal;
		string temp;
		back >> temp;

		//atoi returns 0 if not successful

		if (temp != val) {
			//	cout << "I AM PRINTING AS AN INT!" << temp << " " << val << endl;
			type -= 1;
			//throw DatabaseException(33, val + " not a valid integer.");
		} else
			return "float";
	}
	if (type == 1) {
		stringstream typecast(val);
		float floatVal = 0;
		typecast >> floatVal;
		stringstream back;
		back << floatVal;
		string temp;
		back >> temp;

		//atoi returns 0 if not successful

		//for cases were the float value is 10.00
		if (temp != val) {
			stringstream test2(temp);
			//case for an int
			int other;
			test2 >> other;
			if (other != floatVal || val.find(".0") == -1) {
				type -= 1;
			} else
				return "float";
			//	throw DatabaseException(34, val + " not a valid float.");
		} else
			return "float";
	}

	return "UNKOWN";
}

static string intTypeToString(int type) {
	if (type == 0) {
		return "string";
	} else if (type == 2) {
		return "int";
	} else if (type == 1) {
		return "float";
	} else if (type == 3) {
		return "Date";
	} else if (type == 4) {
		return "Time";
	} else {
		return "Unknown";
	}
}
}
#endif
