/*
 * Query_parser.h
 *
 *  Created on: Jan 31, 2012
 *      Author: gigemjt
 */

#ifndef QUERY_PARSER_H_
#define QUERY_PARSER_H_
#include <iostream>
#include<string>
#include<sstream>
#include<map>
#include<vector>
#include"Database.h"
#include"LogicHandler.h"
#include"ExpressionTree.h"
using namespace std;
using namespace LogicExpression;
class Query_parser {

public:
	static int temp_table_num;
	//this will hold the old columns =
	//the cloumns from the table being quieried
	vector<string> old_columns;
	bool all_columns;
	//this will have a map that maps old columns to new columns
	//most of them will have the same name
	map<string, string> new_columns;
	//this will have the short name meaning without the table part
	map<string, string> short_name_new_columns;
	//this is the string of the receiving tables
	vector<string> tables;
	//this will be a map of table names.columns
	vector<string> join_columns;
	//this will have a map of the string of the column affected and the conditional itself
	map<string, string> conditional;
	vector<ExpressionTree*> trees;
	//this is the name of the new table
	string new_table_name;
	Query_parser(Database* DB);
	void parse(string g);
	void parse_query(string g);
	/**
	 * The main commands
	 */
	void select_parser(string g);
	void from_parser(string g);
	void store_parser(string g);
	void deleteRows(string g); //ADDED

	/**
	 * Commands inside select
	 */
	void single_selection(string g);
	string get_single_selections();
	int selectFunctionsExist();
	string selectFunctionRemove(string input);
	/**
	 * Commands inside from
	 */
	void where_parser(string g);
	void group_by(string g);
	void order_by(string g);
	void table_parser(string g);
	void join_parser(string g);
	bool is_joined_column(string column);
	/**
	 * Commands inside store
	 */
	//none!!!

	/**
	 * Commands for actions
	 */
	void action();
	virtual ~Query_parser();
private:
	Database* db;
};
//int Query_parser::temp_table_num=0;
#endif /* QUERY_PARSER_H_ */
