#include "Table.h"

//Table Constructor
Table::Table(string name)
{
	Table::tableName = name;
}

Table::~Table(void)
{
}


string Table::getTableName(){
	return tableName;
}

int Table::rowCount() {
	if(columnCount() > 0){
		return columnList.begin()->second->rowCount();
	}
	else{
		return 0;
	}
}

int Table::columnCount() {
	return columnList.size();
}

Column * Table::findColumn(string colName) {
	return columnList[colName];
}

void Table::setPrimaryKey(string colName) {
	
	Column *theCol = findColumn(colName);

	if(theCol == NULL) {
		throw DatabaseException(20, colName + " does not exist.");
	}

	theCol->setPrimary(true);
}

void Table::createColumn(string passInName, string passInType) {
	if(findColumn(passInName) != NULL) {
		throw DatabaseException(21, passInName + " already exists.");
	}

	columnList[passInName] = new Column(passInType);
}


/////////BDB//////Check for matching number of columns/////////////////////
void Table::addRow(vector<string> columnNames, vector<string> rowData) {
	for(int i = 0; i < columnNames.size(); i++) {
		Column *thisCol = findColumn(columnNames[i]);
		if(thisCol == NULL) {
			throw DatabaseException(20, "Column " + columnNames[i] + " does not exist.");
		}
		if(thisCol->isPrimaryKey() && thisCol->valExists(rowData[i])) {
			throw DatabaseException(21, rowData[i] + " already exists in column" + columnNames[i] + ".");
		}
		thisCol->addRow(rowData[i]);
	}
}

string Table::printColumns(){
	string s = "";
	map<string, Column *>::iterator it;
	
	for (it=columnList.begin() ; it != columnList.end(); it++){
		s += it->first;
		s += it->second->printDataList();
		s += "; ";
	}
	
	return s;
}

string Table::printSelf(){

	ostringstream stringForConversion;
	ostringstream stringForConversion2;

	string s = getTableName() + ", ";
	
	stringForConversion << columnCount();
	s += stringForConversion.str() + ", "; 
	
	stringForConversion2 << rowCount();
	s += stringForConversion2.str() + "; ";
	
	s += printColumns();
	
	return s;
}

vector<string> Table::getRow(int rowIndex) {

	vector<string> returnVect;

	map<string, Column *>::iterator it;
	for ( it=columnList.begin() ; it != columnList.end(); it++ ) {
		returnVect.push_back(it->second->getValueAtRowIndex(rowIndex));
	}

	return returnVect;
}
