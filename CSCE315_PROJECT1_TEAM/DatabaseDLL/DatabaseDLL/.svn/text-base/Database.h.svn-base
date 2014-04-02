/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The header file for the Database class
 Learn more at http://goo.gl/lTVVA
*/
#ifndef __Database_H_
#define __Database_H_

#include <vector>
#include "Table.h"
#include "ExpressionTree.h"
#include "Column.h"
#include<map>
class parser;
using namespace std;
class Query_parser;
class Database {

private:
	map<string, Table*> tableList;
	string errorMessage;
	parser *dbParser;
	bool debug;
public:
	Database();
	~Database();

	int create(string input);
	int insert(string input);
	int update(string input);
	string query(string input);
	int deleteRows(string input);
	int drop(string input);
	int recordCount(string tableName = "");
	string list(string tableName);
	string getErrorMessage();

	void setErrorMessage(string msg);
	Table* queryParsing(Query_parser* p,string oldTableName,Table* newTable);
	void completeQueryParsing(Query_parser* p);
	void normalQuery(Query_parser* p,string oldTableName,Table* newTable);
	void updateParsing(Query_parser* p, vector<string> columnNames,
			vector<string> columnData, string tableName);
	void deleteParsing(Query_parser* p);
	int countStatement(Query_parser* p);
	float sumStatement(Query_parser* p, string columnName);
	float minMaxStatement(Query_parser* p, string columnName, bool min);
	void addRowToTable(string tableName, vector<string> columnNames,
			vector<string> rowData);
	int countRecordsByTable(string tableName);
	int countRecords();
	int countColumnsByTable(string tableName);
	void createTable(string tableName);
	Table* createPartialTable(Query_parser* parser,string tableName);
	void combineTables(vector<Table*> tables,Query_parser* parser,Table* );
	void addTable(Table* t,string tableName);
	int deleteTable(string tableName);
	Table *findTable(string tableName);
	Column* findColumn(string totalName);
	string printTable(string tableName);
	string printAllTables();
	void setPrimaryKey(string tableName, string colName);
	void setDebug(bool input);
};

#endif
