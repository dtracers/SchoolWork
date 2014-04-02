#include "Database.h"

//Constructor & Destructor
Database::Database(void)
{
	//databaseParser(this);
}

Database::~Database(void)
{
}

/*	
	User functions 
*/

int Database::create(string input){
	//databaseParser.parse(input);
	return 0;
}

int Database::insert(string input){
	return 0;
}

int Database::update(string input){
	return 0;
}

string Database::query(string input){
	string temp = "default";
	return temp;
}	

int Database::deleteRows(string input){ ///////Had to change in API specification, delete special word ANC
	return 0;
}

int Database::drop(string input){
	return deleteTable(input);
}

//return number of rows in given table, or if not specified, the whole database
int Database::recordCount(string input){
	if(input.size() == 0){
		return countRecords();
	}
	else{
		return countRecordsByTable(input);
	}
}

//Prints out all tables from database
string Database::list(string input){
	string s = printTable(input);
	return s;
}

//Returns errorMessage data member
string Database::getErrorMessage(){
	return errorMessage;
}


/*
	Helper functions used to do work
*/
	
//Set the Primary Key for a table given the table name and given the column name
void Database::setPrimaryKey(string tableName, string colName) {
	Table *theTable = findTable(tableName);

	if(theTable == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	theTable->setPrimaryKey(colName);
}

//Add a row to a table given the table name, the column names, and the data for the rows
void Database::addRowToTable(string tableName, vector<string> columnNames, vector<string> rowData) {

	if(columnNames.size() != rowData.size()) {
		throw DatabaseException(12);
	}

	Table * theTable = findTable(tableName);
	
	if(theTable == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	theTable->addRow(columnNames, rowData);
}

//Find a table given the name
Table * Database::findTable(string tableName) {
	return tableList[tableName];
}

//Delete an entire table from a database
int Database::deleteTable(string tableName){
	if(findTable(tableName) == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	map<string, Table*>::iterator it = tableList.find(tableName);
	tableList.erase(it);
	return 0;
}

//Create an empty table
void Database::createTable(string tableName) {
	if(findTable(tableName) != NULL) {
		throw DatabaseException(11, tableName + " already exist.");
	}

	tableList[tableName] = new Table(tableName);
}

//Create a column given the name of the table, name of the column, and type of the column
void Database::createTableColumn(string tableName, string colName, string type) {
	
	if(findTable(tableName) == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	tableList[tableName]->createColumn(colName, type);
}

//Count rows of a single table given the name
int Database::countRecordsByTable(string tableName){
	if(findTable(tableName) == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	return tableList[tableName]->rowCount();

}

//Count all the rows of the entire database
int Database::countRecords(){
	int totalRecords = 0;
	
	map<string,Table*>::iterator it;
	for ( it=tableList.begin() ; it != tableList.end(); it++ ) {
		totalRecords += countRecordsByTable(it->first);
	}
	
	return totalRecords;
}

//Print a single table given the name
string Database::printTable(string tableName){
	string s = "";
	Table* table=findTable(tableName);
	if(table == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}
	s = table->printSelf();
	return s;
}

//output to the screen all tables in database
string Database::printAllTables()
{
	string s = "";
	map<string,Table*>::iterator it;
	for(it=tableList.begin();it!=tableList.end();it++)
	{
		s += printTable((*it).first);
	}
	return s;
}
