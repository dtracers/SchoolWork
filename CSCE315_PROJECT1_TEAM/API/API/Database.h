#ifndef __Database_H_
#define __Database_H_

#include <vector>
#include "Table.h"
//#include "parser.h"
#include<map>
using namespace std;

class Database
{
public:
	Database();
	~Database();

	int create(string input);
	int insert(string input);
	int update(string input);
	string query(string input);		
	int deleteRows(string input); ///////Had to change in API specification, delete special word ANC
	int drop(string input); // :)
	int recordCount(string input = ""); // :)
	string list(string input); // :)
	string getErrorMessage();

private:
	map<string, Table*> tableList;
	string errorMessage;
	//Parser databaseParser;

public:
	void addRowToTable(string tableName, vector<string> columnNames, vector<string> rowData);
	int countRecordsByTable(string tableName);
	int countRecords();
	void createTable(string tableName);
	void createTableColumn(string tableName, string colName, string type);
	int deleteTable(string tableName);
	Table *findTable(string tableName);
	string printTable(string tableName);
	string printAllTables();
	void setPrimaryKey(string tableName, string colName);
};

#endif
