/*
 * parser.h
 *
 *  Created on: Jan 31, 2012
 *      Author: gigemjt
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <iostream>
#include<string>
#include<sstream>
#include"Table_parser.h"
#include"Query_parser.h"
using namespace std;
class parser {
public:
	parser(Database* db);
	void parse(string g);
	void find_command(string g);
	string return_last_table();
	virtual ~parser();
private:
	string new_table;
	Database* db;
};

#endif /* PARSER_H_ */
