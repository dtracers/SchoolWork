/*
 * creatingtable.h
 *
 *  Created on: Jan 30, 2012
 *      Author: gigemjt
 */

#ifndef CREATINGTABLE_H_
#define CREATINGTABLE_H_
#include<string>
#include<vector>
#include"Database.h"
#include"Table.h"
using namespace std;
class Table_parser {
public:

	Table_parser(Database* DB);
	virtual ~Table_parser();
	void create_table(string statement);
	void insert(string statement);
	void set_name(string statement);
	void data_types_and_their_name(string g,Table* b);
	void primary_key(Table* table,string primary);
private:
	Database* db;
	string table_name;
};

#endif /* CREATINGTABLE_H_ */
