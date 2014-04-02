/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The header file for the Table class
*/
#ifndef __Table_H_
#define __Table_H_

#include <vector>
#include "Column.h"

class Table {
private:
	map<string, Column *> columnList;
	string tableName;
public:
	Table(string name);
	~Table(void);
	void addRow(vector<string> columnNames, vector<string> rowData);
	void deleteAllRows();
	int rowCount();
	int columnCount();
	string getTableName();
	Column *findColumn(string colName);
	void createColumn(string name, string passInType);
	void createColumn(string name, Column* col);
	string printColumns();
	void setPrimaryKey(string colName);
	string printSelf();
	vector<string> getRow(int rowIndex);
	vector<string> columnNames();
	void updateRow(int rowIndex, vector<string> columnNames,
			vector<string> rowData);
	void deleteRow(int rowIndex);
};

#endif
