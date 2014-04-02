/*
 * creatingtable.cpp
 *
 *  Created on: Jan 30, 2012
 *      Author: gigemjt
 */

#include "Table_parser.h"
#include "global_parsing_methods.h"
#include "Query_parser.h"
#include<sstream>
#include<iostream>

Table_parser::Table_parser(Database* DB) {
	db = DB;
}

/**
 * This will hold the entire statement as one string!!!
 */
void Table_parser::create_table(string statement) {
	stringstream m(statement);
	string name;
	string pre_junk;

	//this is to through out the create table
	//if that is already consumed then we shall get rid of this
	m >> pre_junk;
	m >> pre_junk;

	m >> name;
	set_name(name);

	int pos = statement.find_first_of('(');
	pos += 1;
	//goes through ALL data types!!!! separated by comma
	int final_index;
	Table* table = db->findTable(table_name);
	
	while (pos > 0) {
		final_index = pos;
		int next = statement.find_first_of(',', pos);
		string data = "";
		for (int index = pos; index < next; index++) {
			data += statement[index];
		}
		//this will do data type thingy mabobbers
		data_types_and_their_name(data, table);
		pos = next + 1;
	}
	string data = "";
	int last_index = statement.find_last_of(")");
	for (int index = final_index; index < last_index; index++) {
		data += statement[index];
	}
	
	data_types_and_their_name(data, table);
}

/**
 * This will take in the data types and set them and the names and set those
 */
void Table_parser::data_types_and_their_name(string column, Table* table) {
	if (column.length() < 1) {
		return;
	}
	stringstream data(column);
	string name;
	string type;
	data >> name;
	data >> type;

	if (name == "PRIMARY" && type == "KEY") {
		primary_key(table, column);
		return;
	} else {
		cout << " name is " << name;
		cout << " type is " << type << endl;
	}
	table->createColumn(name, type);
}

/**
 * This will set the name of the table
 */
void Table_parser::set_name(string g) {
	db->createTable(g);
	table_name = g;
	cout << "The table is named " << g << endl;
}

/**
 * This will parse the columns in the format of
 * Table NAME table_name ... (column1,column2,colum3...) ... (data1,data2,data3)
 * it will put the first group into columnNames
 * and put the second group into columnData
 */
void Table_parser::column_parser(string statement) {
	stringstream stream(statement);
	string pre_junk;
	string table_name;
	stream >> pre_junk;
	stream >> pre_junk;
	stream >> table_name;
	cout << "table name: " << table_name << endl;
	
	this->table_name = table_name;
	
	int first_open = statement.find_first_of("(");
	int first_close = statement.find_first_of(")");
	int second_open = statement.find_first_of("(", first_close);
	int second_close = statement.find_first_of(")", second_open);
	first_open++;
	second_open++;
	string first = statement.substr(first_open, first_close - first_open);
	string second = statement.substr(second_open, second_close - second_open);
	vector<string> first_group = globalParse::get_separate_statments(first,
			",");
	vector<string> second_group = globalParse::get_separate_statments(second,
			",");
	for (int k = 0; k < first_group.size(); k++) {
		cout << "COLUMN " << first_group[k] << " = " << second_group[k] << endl;
	}
	columnNames = first_group;
	columnData = second_group;
}

/**
 * This will insert a new column into the insert statement
 */
void Table_parser::insert(string statement) {
	column_parser(statement);
	cout << "ADDING ROW!!!" << endl;
	Table* table = db->findTable(table_name);
	table->addRow(columnNames, columnData);
	cout << "row added successfully" << endl;
}

void Table_parser::update(string statement) {
	stringstream stream(statement);
	string pre_junk;
	stream >> pre_junk;
	stream >> pre_junk;
	string tableName;
	stream >> tableName;

	column_parser(statement);
	Query_parser crc(db);
	crc.where_parser(statement);

	db->updateParsing(&crc, columnNames, columnData, tableName);
}

/**
 * This will set the primary key
 * it takes in the column name of the primary key
 */
void Table_parser::primary_key(Table * table, string primary) {
	stringstream data(primary);
	string pre_junk;
	data >> pre_junk;
	data >> pre_junk;
	string the_key;
	data >> the_key;
	table->setPrimaryKey(the_key);
	cout << " setting the primary key to " << the_key << "\n";
}
Table_parser::~Table_parser() {
	
}
