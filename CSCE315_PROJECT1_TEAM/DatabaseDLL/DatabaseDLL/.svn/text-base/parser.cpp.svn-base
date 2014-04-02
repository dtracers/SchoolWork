/*
 * parser.cpp
 *
 *  Created on: Jan 31, 2012
 *      Author: gigemjt
 */

#include "parser.h"
#include "Database.h"
#include "Query_parser.h"
parser::parser(Database* DB) {
	db = DB;
}
void parser::parse(string g) {
	int old_index = 0;
	int instruction_index = g.find_first_of(';');
	while (instruction_index >= 0) {
		string instruction = g.substr(old_index, instruction_index - old_index);
		find_command(instruction);
		//here comment
		cout << "\nSUCCESS\n\n\n" << endl;
		old_index = instruction_index + 1;
		instruction_index = g.find_first_of(';', old_index);
		//cerr<<"the insex is "<<old_index<<" length is "<<g.length()<<"\n";
	}
	//db->printAllTables();
}
string parser::return_last_table() {
	return new_table;
}
void parser::find_command(string command) {
	stringstream stream(command);
	string first_word;
	string second_word;

	stream >> first_word;
	stream >> second_word;
	//from these two the command type should be able to be found

	//FIRST COMMAND !!!!
	if (first_word == "CREATE" && second_word == "TABLE") {
		cout << "THE COMMAND IS CREATING TABLE" << endl;
		Table_parser crc(db);
		crc.create_table(command);
	} else if (first_word == "SELECT") {
		cout << "THE COMMAND IS QUERYING TABLE" << endl;
		Query_parser crc(db);
		crc.parse(command);
		new_table = crc.new_table_name;
	} else if (first_word == "INSERT" && second_word == "INTO") {
		cout << "THE COMMAND IS INSERTING" << endl;
		Table_parser crc(db);
		crc.insert(command);
	} else if (first_word == "PRINT" && second_word == "ALL") {
		cout << "THE COMMAND IS PRINT ALL TABLES" << endl;
		cout<<db->printAllTables()<<endl;
	} else if (first_word == "UPDATE") {
		//UPDATE TABLE table_name SET (column1_name, column2_name, ...) VALUES (column1_value, column2_value, ...) [WHERE Conditionals]
		cout << "THE COMMAND IS UPDATE" << endl;
		Table_parser crc(db);
		crc.update(command);
		//where parse in query_parser, get from       from parser
		//column parser in table_parser
		//queryParsing in database
	} else if (first_word == "DELETE" && second_word == "FROM") { //ADDED
		cout << "THE COMMAND IS DELETEROWS" << endl;
		Query_parser crc(db);
		crc.deleteRows(command);

		//throw "DELETE NOT IMPLEMENTED";
		//“DELETE FROM table_name [WHERE Conditionals]”
		//Optional where clause. If not there then delete all rows.
	} else if (first_word == "STOP") { //ADDED
		throw DatabaseException(-1, "PROGRAM STOPPED SUCCESFULLY");
	}
}
parser::~parser() {
	// TODO Auto-generated destructor stub
}
