/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The table class which holds columns
 */
#include "Table.h"

//Table Constructor
Table::Table(string name) {
	Table::tableName = name;
}

Table::~Table(void) {
}

string Table::getTableName() {
	return tableName;
}

/*
 Returns the first columns row count
*/
int Table::rowCount() {
	if (columnCount() > 0) {
		map<string, Column *>::iterator it;
		vector<Column*> smalls;
		int max=-1;
			for (it = columnList.begin(); it != columnList.end(); it++) {
				if(it->second->rowCount()>max)
				{
					max=it->second->rowCount();
					smalls.push_back(it->second);
				}else
				{
					smalls.push_back(it->second);
				}
			}
			return max;
	} else {
		return 0;
	}
}

/*
 Set the primary key of the table
*/
int Table::columnCount() {
	return columnList.size();
}

Column * Table::findColumn(string colName) {
	return columnList[colName];
}

/*
 Set the primary key of the table
*/
void Table::setPrimaryKey(string colName) {

	Column *theCol = findColumn(colName);

	if (theCol == NULL) {
		throw DatabaseException(20, colName + " does not exist.");
	}

	theCol->setPrimary(true);
}

/*
 A middle man since varchar needs parsing to get the length
*/
void Table::createColumn(string passInName, Column* col) {
	string type = col->getColumnType();
	if (type == "varchar") {
		stringstream m;
		m << col->getVarCharMaxLength();
		string m2;
		m >> m2;
		m2 = "(" + m2 + ")";
		type += m2;
	}
	createColumn(passInName, type);
	//makes sure column primaies are the same
	findColumn(passInName)->setPrimary(col->isPrimaryKey());
}

/*
 Create the column
*/
void Table::createColumn(string passInName, string passInType) {
	if (findColumn(passInName) != NULL) {
		throw DatabaseException(21, passInName + " already exists.");
	}

	columnList[passInName] = new Column(passInType);
}

/*
 Add a row. Loops through the columns and adds the row
*/
void Table::addRow(vector<string> columnNames, vector<string> rowData) {
	vector<Column*> smalls;
	for (int i = 0; i < columnNames.size(); i++) {
		Column *thisCol = findColumn(columnNames[i]);
		if (thisCol == NULL) {
			throw DatabaseException(20,
					"Column " + columnNames[i] + " does not exist.");
		}
		//default rows dont count
		if ((rowData[i]!="D3FAL7")&&thisCol->isPrimaryKey() && thisCol->valExists(rowData[i])) {
			throw DatabaseException(
					22,
					rowData[i] + " already exists in column" + columnNames[i]
							+ ".");
		}

		thisCol->addRow(rowData[i]);
		smalls.push_back(thisCol);

	}
	map<string, Column *>::iterator it;
	for (it = columnList.begin(); it != columnList.end(); it++)
	{
		bool inside=false;
		for(int k=0;k<smalls.size();k++)
		{
			if(smalls[k]==it->second)
			{
				inside=true;
			}
		}
		if(!inside)
		{
			it->second->addRow("D3FAL7");
		}
	}
}

void Table::deleteAllRows() {
	map<string, Column*>::iterator it;
	it = it = columnList.begin();
	columnList.erase(it, columnList.end());
}

/*
 Delete a row using the index. Loop through the columns and delete that index
*/
void Table::deleteRow(int rowIndex) {
	if (rowIndex > rowCount()) {
		throw DatabaseException(23, rowIndex + " out of range.");
	}

	map<string, Column *>::iterator columnIt;

	for (columnIt = columnList.begin(); columnIt != columnList.end();
			columnIt++) {
		columnIt->second->deleteRow(rowIndex);
	}
}

/*
 Update the row at the index with the names and data
*/
void Table::updateRow(int rowIndex, vector<string> columnNames,
		vector<string> rowData) {
	if (rowIndex > rowCount()) {
		throw DatabaseException(23, rowIndex + " out of range.");
	}

	//Loop through the columns and change the values at the index if the column exists.
	for (int i = 0; i < columnNames.size(); i++) {
		if (columnList[columnNames[i]] == NULL) {
			throw DatabaseException(20, columnNames[i] + " does not exist.");
		}

		columnList[columnNames[i]]->addRow(rowData[i], rowIndex);
	}
}

/*
 Loop through the columns and print the data
*/
string Table::printColumns() {
	string s = "";
	map<string, Column *>::iterator it;

	for (it = columnList.begin(); it != columnList.end(); it++) {
		s += it->first;
		s += it->second->printDataList();
		s += ";\n";
	}

	return s;
}

/*
 Print the table information and then the columns
*/
string Table::printSelf() {

	ostringstream stringForConversion;
	ostringstream stringForConversion2;

	string s = getTableName() + ", ";

	stringForConversion << columnCount();
	s += "Columns: " + stringForConversion.str() + ", ";

	stringForConversion2 << rowCount();
	s += "Rows: " + stringForConversion2.str() + ";\n";

	s += printColumns();
	return s;
}

/*
 Returns the row in a vector of strings
*/
vector<string> Table::getRow(int rowIndex) {

	vector<string> returnVect;

	map<string, Column *>::iterator it;
	for (it = columnList.begin(); it != columnList.end(); it++) {
		returnVect.push_back(it->second->getValueAtRowIndex(rowIndex));
	}

	return returnVect;
}

/*
 Get the column names
*/
vector<string> Table::columnNames() {

	vector<string> returnVect;

	map<string, Column *>::iterator columnIt;
	for (columnIt = columnList.begin(); columnIt != columnList.end();
			columnIt++) {
		returnVect.push_back(columnIt->first);
	}

	return returnVect;
}

