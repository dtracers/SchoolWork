#ifndef __Table_H_
#define __Table_H_

#include <vector>
#include "Column.h"

class Table
{
private:
	map<string, Column *> columnList;
	string tableName;
public:
	Table(string name);
	~Table(void);
	void addRow(vector<string> columnNames, vector<string> rowData);
	int rowCount();
	int columnCount();
	string getTableName();
	Column *findColumn(string colName);
	void createColumn(string name, string passInType); 
	string printColumns();
	void setPrimaryKey(string colName);
	string printSelf();
	vector<string> getRow(int rowIndex);
};

#endif
