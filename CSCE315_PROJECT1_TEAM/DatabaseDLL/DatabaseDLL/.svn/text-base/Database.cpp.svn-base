/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The class that stores the actual database information like tables, etc.
 The functions are called by the middle-man FunctionalDatabaseDLL
 The functions return 0 if successful or a # for a specific exception.
*/
#include "Database.h"
#include "parser.h"
#include "global_parsing_methods.h"
#include "OPERATIONS.cpp"

Database::Database() {
	dbParser = new parser(this);
	debug = false;
}
Database::~Database() {
	delete dbParser;
}

/*
 The following methods differ depending on the manipulation
 the user is wanting to do on the database. All methods
 simply call the parser to parse the string.
*/

//Create a table
int Database::create(string input) {
	if(debug)
		cout<<"input is:\n"<<input<<endl;
	if(dbParser == NULL)
	{
		cout << "NULL" << endl;
		dbParser = new parser(this);
	}
	
	dbParser->parse(input);
	return 0;
}

//Delete from the database 
int Database::deleteRows(string input) {
	if(debug)
		cout<<"input is:\n"<<input<<endl;
	if(dbParser==NULL)
	{
		cout<<"NULL"<<endl;
		dbParser=new parser(this);
	}
	dbParser->parse(input);

	return 0;
}

//Delete a whole table from the database
int Database::drop(string tableName) {
	if(debug)
		cout<<"input is:\n"<<tableName<<endl;
	if (findTable(tableName) == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	map<string, Table*>::iterator it = tableList.find(tableName);
	tableList.erase(it);

	return 0;
}

//Insert into the database
int Database::insert(string input) {
	if(debug)
		cout<<"input is:\n"<<input<<endl;
	if(dbParser==NULL)
	{
		cout<<"NULL"<<endl;
		dbParser=new parser(this);
	}
	dbParser->parse(input);
	return 0;
}

//Query the database to return results
string Database::query(string input) {
	if(debug)
		cout<<"input is:\n"<<input<<endl;
	if(dbParser==NULL)
	{
		cout<<"NULL"<<endl;
		dbParser=new parser(this);
	}
	dbParser->parse(input);
	
	string tableName = dbParser->return_last_table();

	return printTable(tableName);
}

//Update data in a table
int Database::update(string input) {
	if(debug)
		cout<<"input is:\n"<<input<<endl;
	if(dbParser==NULL)
	{
		cout<<"NULL"<<endl;
		dbParser=new parser(this);
	}
	dbParser->parse(input);
	return 0;
}
/*
 End Database manipulation methods
*/

string Database::list(string tableName) {
	if(debug)
		cout<<"input is:\n"<<tableName<<endl;
	string result = printTable(tableName);
	return result;
}

/*
 Set the latest error message for the user to query
*/
void Database::setErrorMessage(string msg) {
	errorMessage = msg;
}
string Database::getErrorMessage() {
	return errorMessage;
}

/*
 Returns the number of rows in the tableName.
 If tableName is empty, return the sum of all rows in all tables
*/
int Database::recordCount(string tableName) {
	if(debug) {
		cout<<"input is:\n"<<tableName<<endl;
	}
	//If no table specified, get entire table tuple count
	if (tableName.size() == 0) {
		int totalRecords = 0;

		map<string, Table*>::iterator it;
		for (it = tableList.begin(); it != tableList.end(); it++) {
			totalRecords += countRecordsByTable(it->first);
		}

		return totalRecords;
	} else {
		return countRecordsByTable(tableName);
	}
}


/*
 Functions used internally but need to be public
*/


Table* Database::findTable(string tableName) {
	return tableList[tableName];
}

/*
 Finds a column. The input is Table.ColumnName
*/
Column* Database::findColumn(string totalName) {
	vector<string> fullName = globalParse::get_separate_statments(totalName,
			".");

	Table * table = findTable(fullName[0]);

	if (table == NULL) {
		throw DatabaseException(10, fullName[0] + " does not exist.");
	}

	Column * col = table->findColumn(fullName[1]);

	if (col == NULL) {
		throw DatabaseException(20, fullName[1] + " does not exist.");
	}

	return col;
}

/*
 Add a row to the table given the column names and data for the rows
*/
void Database::addRowToTable(string tableName, vector<string> columnNames,
		vector<string> rowData) {

	if (columnNames.size() != rowData.size()) {
		throw DatabaseException(12);
	}

	Table *theTable = findTable(tableName);

	if (theTable == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	theTable->addRow(columnNames, rowData);
}

/*
 Find the row count of a table
*/
int Database::countRecordsByTable(string tableName) {
	if (findTable(tableName) == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	return tableList[tableName]->rowCount();
}
/*
 Find the column count of a table
*/
int Database::countColumnsByTable(string tableName) {
	if (findTable(tableName) == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}
	return tableList[tableName]->columnCount();
}
/*
 * returns 1 if table is succesfully deleted
 */
int Database::deleteTable(string tableName) {
	if (findTable(tableName) == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}
	drop(tableName);
	if (tableList[tableName] != NULL) {
		cout << "REMOVING " << tableName << endl;
		tableList[tableName] = NULL;
	}

	return 1;
}

/*
 Create an empty table
*/
void Database::createTable(string tableName) {
	if (findTable(tableName) != NULL) {
		throw DatabaseException(11, tableName + " already exist.");
	}

	tableList[tableName] = new Table(tableName);
}

/*
 Add a table already created
*/
void Database::addTable(Table* t, string tableName) {
	if (findTable(tableName) != NULL) {
		throw DatabaseException(11, tableName + " already exist.");
	}

	tableList[tableName] = t;
}

/*
 Print the table information given tableName
*/
string Database::printTable(string tableName) {
	string s = "";
	Table* table = findTable(tableName);
	if (table == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}
	s = table->printSelf();
	return s;
}

/*
 Create a partial table. Used when querying
*/
Table* Database::createPartialTable(Query_parser* parser, string tableName) {
	//Return the already created table everything is fine
	if (parser->tables.size() == 1)
		return findTable(parser->new_table_name);

	//actual stuff  table size > 1
	vector<string> old_columns = parser->old_columns;
	Table* t = new Table("partial" + tableName);
	if(debug)
		cout<<"partila table is "<<t->printSelf()<<endl;
	Table* t_old = findTable(parser->new_table_name);
	for (int k = 0; k < old_columns.size(); k++) {
		string removed = parser->selectFunctionRemove(old_columns[k]);
		
		Column* col;
		
		vector<string> fullName = globalParse::get_separate_statments(removed,
				".");
		if (fullName[0] != tableName && fullName.size() > 1) {
			//if it isnt this table idc
			continue;
		} else if (fullName.size() == 1) {
			//then it is the joined column
			col = t_old->findColumn(parser->new_columns[removed]);
			if (col == NULL)
				throw DatabaseException(20, removed + " does not exist.");
		} else
			col = findColumn(removed);
		//cout << "DOES IT WORK?" << endl;
		//this may not work
		t->createColumn(parser->new_columns[removed], col);
	}
	return t;
}

/*
 Complete the query parsing by joining the table results
*/
void Database::completeQueryParsing(Query_parser* parser) {
	vector<Table*> tables;
	vector<string> tableNames = parser->tables;
	for (int k = 0; k < tableNames.size(); k++) {
		

		Table* t = createPartialTable(parser, tableNames[k]);
		if(debug)
		{
			cout<<t->printSelf()<<endl;
		}
		if (tableNames.size() > 1)
			addTable(t, t->getTableName());
		tables.push_back(queryParsing(parser, tableNames[k], t));
		
	}
	Table* newTable = findTable(parser->new_table_name);
	if (newTable == NULL) {
		createTable(parser->new_table_name);
		newTable = findTable(parser->new_table_name);
	}
	if(debug)
	{
		cout<<"new table is "<<endl;
		cout<<newTable->printSelf()<<endl;
	}
	if (tables.size() == 1) {
		this->deleteTable(parser->new_table_name);
		this->addTable(tables[0], parser->new_table_name);
	} else {
		combineTables(tables, parser, newTable);
	}

	if (tables.size() > 1) {
		for (int k = 0; k < tables.size(); k++) {
			deleteTable(tables[k]->getTableName());
		}
	}
}

/*
 Either passes the data to normalQuery or continues if the SELECT statement has functions like SUM, etc
 Calculates the SELECT functions and adds the resulting value to the new table
*/
Table* Database::queryParsing(Query_parser* parser, string oldTableName,
		Table* newTable) {
	if(debug)
		cout<<"MADE IT THIS FAR IN QUERY PARSING"<<endl;
	vector<LogicExpression::ExpressionTree*> expTree = parser->trees;
	string newTableName = parser->new_table_name;
	map<string, string> oldToNewColumns = parser->new_columns;
	Table *oldTable = findTable(oldTableName);

	//Make sure the tables exist
	if (oldTable == NULL) {
		throw DatabaseException(10, oldTableName + " does not exist.");
	} else if (newTable == NULL) {
		throw DatabaseException(10, newTableName + " does not exist.");
	}
	int selectFuncsExist = parser->selectFunctionsExist();

	if (selectFuncsExist == -1) {
		throw DatabaseException(
				25,
				"SELECT commands must all be select functions (Sum, Count, Min, or Max).");
	}

	vector<string> oldTableColumnNames = oldTable->columnNames();
	
	//If select functions aren't used, then call the normal query parser
	if (selectFuncsExist == 0) {
		if(debug)
		{
			cout<<"NORMAL QUERY"<<endl;
		}
		normalQuery(parser, oldTableName, newTable);
	//Must find the select function and calculate
	} else {
		map<string, string>::iterator oldToNewColumnsIt;
		vector<string> columnNamesToAdd;
		vector<string> columnDataToAdd;

		for (oldToNewColumnsIt = oldToNewColumns.begin();
				oldToNewColumnsIt != oldToNewColumns.end();
				oldToNewColumnsIt++) {
			string oldName = oldToNewColumnsIt->first;
			string newName = oldToNewColumnsIt->second;
			if (newName == "") {
				continue;
			}
			//cout<<"switch "<<oldName<<"="<<newName<<endl;
			columnNamesToAdd.push_back(newName);
			string str = "";
			stringstream strstr;

			if (oldName.find("SUM") != string::npos) {
				strstr
						<< sumStatement(parser,
								parser->selectFunctionRemove(oldName));
			} else if (oldName.find("COUNT") != string::npos) {
				strstr << countStatement(parser);
			} else if (oldName.find("MIN") != string::npos) {
				strstr
						<< minMaxStatement(parser,
								parser->selectFunctionRemove(oldName), true);
			} else if (oldName.find("MAX") != string::npos) {
				strstr
						<< minMaxStatement(parser,
								parser->selectFunctionRemove(oldName), false);
			}

			strstr >> str;

			columnDataToAdd.push_back(str);
		}
		addRowToTable(newTable->getTableName(), columnNamesToAdd,
				columnDataToAdd);
	}
	
	return newTable;
}

/*
 The query parsing function that does not contain SELECT functions
 This loops through the rows and if they pass, adds it to the new table
*/
void Database::normalQuery(Query_parser* parser, string oldTableName,
		Table* newTable) {
	vector<LogicExpression::ExpressionTree*> expTree = parser->trees;
	string newTableName = parser->new_table_name;
	map<string, string> oldToNewColumns = parser->new_columns;
	Table *oldTable = findTable(oldTableName);
	vector<string> oldTableColumnNames = oldTable->columnNames();
	//Loop through the rows.
	//If each row passes the test, then add it to the new table
	for (int i = 0; i < oldTable->rowCount(); i++) {

		vector<string> thisRow = oldTable->getRow(i);

		//Make sure the row passes each expression
		bool rowPasses = false;
		
		for (int k = 0; k < expTree.size(); k++) {
		
			rowPasses = expTree[k]->isTrue(oldTableColumnNames, thisRow);
			
			if (!rowPasses) {
				break;
			}
		}

		//If there's not comparators, then it auto passes!
		if (expTree.size() == 0) {
			rowPasses = true;
		}

		//Now if they used the AS operator, then we need to
		//assign the values to the new column names
		if (rowPasses) {
			//Loop through the mapping and set the new column names
			//Then find the old column name's value to replace
			map<string, string>::iterator oldToNewColumnsIt;
			vector<string> columnNamesToAdd;
			vector<string> columnDataToAdd;

			for (oldToNewColumnsIt = oldToNewColumns.begin();
					oldToNewColumnsIt != oldToNewColumns.end();
					oldToNewColumnsIt++) {

				string oldName = oldToNewColumnsIt->first;

				string newName = oldToNewColumnsIt->second;
				vector<string> fullName = globalParse::get_separate_statments(
						oldName, ".");
				if (fullName.size() > 1) {
					if (fullName[0] != oldTableName) {
						//this will be different dont care about those
						continue;
					}
					else if (fullName[0] == oldTableName) {
						oldName = fullName[1];
					}
				}
				columnNamesToAdd.push_back(newName);

				//Loop through the column names and at that
				//index add the data from the row
				bool columnFound = false;
				for (int j = 0; j < oldTableColumnNames.size(); j++) {
					if (oldTableColumnNames[j] == oldName) {
						columnDataToAdd.push_back(thisRow[j]);
						columnFound = true;
					}
				}

				//Make sure the old column name was found
				if (!columnFound) {
					throw DatabaseException(20, oldName + " does not exist");
				}
			}

			//Now add the successful row!
			//addRowToTable(newTableName, columnNamesToAdd, columnDataToAdd);
			addRowToTable(newTable->getTableName(), columnNamesToAdd,
					columnDataToAdd);
		}
	}
}

/*
 Same at queryParsing, but will delete the row if it passes
*/
void Database::deleteParsing(Query_parser* p) {

	string tableName = p->tables[0];
	vector<LogicExpression::ExpressionTree*> expTree = p->trees;

	Table * table = findTable(tableName);

	if (table == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	vector<string> columnNames = table->columnNames();

	//Loop through the rows.
	//If each row passes the test, then remove it from the table
	for (int i = 0; i < table->rowCount(); i++) {

		vector<string> thisRow = table->getRow(i);

		//Make sure the row passes each exression
		bool rowPasses = false;
		for (int k = 0; k < expTree.size(); k++) {
			//FIXX: IS THIS RIGHT?
			rowPasses = expTree[k]->isTrue(columnNames, thisRow);
			if (!rowPasses) {
				break;
			}
		}

		//If there's not comparators, then it auto passes!
		if (expTree.size() == 0) {
			rowPasses = true;
		}

		//Now if they used the AS operator, then we need to
		//assign the values to the new column names
		if (rowPasses) {
			table->deleteRow(i);
		}
	}
}

/*
 Sums the column's values
*/
float Database::sumStatement(Query_parser* p, string columnName) {
	string tableName = p->tables[0];
	vector<LogicExpression::ExpressionTree*> expTree = p->trees;

	Table * table = findTable(tableName);

	if (table == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	Column * column = table->findColumn(columnName);

	if (column == NULL) {
		throw DatabaseException(20, columnName + " does not exist.");
	}

	string colType = column->getColumnType();
	if (colType != "int" && colType != "float") {
		throw DatabaseException(24,
				columnName + " must be of type int or float");
	}

	vector<string> columnNames = table->columnNames();
	double sum = 0.0;
	int colIndex = -1;

	for (int i = 0; i < columnNames.size(); i++) {
		if (columnNames[i] == columnName) {
			colIndex = i;
			break;
		}
	}

	//Loop through the rows.
	//If each row passes the test, then remove it from the table
	for (int i = 0; i < table->rowCount(); i++) {
		vector<string> thisRow = table->getRow(i);

		//Make sure the row passes each exression
		bool rowPasses = false;
		for (int k = 0; k < expTree.size(); k++) {
			//FIXX: IS THIS RIGHT?
			rowPasses = expTree[k]->isTrue(columnNames, thisRow);
			if (!rowPasses) {
				break;
			}
		}

		//If there's not comparators, then it auto passes!
		if (expTree.size() == 0) {
			rowPasses = true;
		}

		//Now if they used the AS operator, then we need to
		//assign the values to the new column names
		if (rowPasses) {
			sum += atof(thisRow[colIndex].c_str());
			//	cerr<<"adding! "<<sum<<endl;
		}
	}

	return sum;
}

/*
 Finds the min or max of the column
*/
float Database::minMaxStatement(Query_parser* p, string columnName, bool min) { //ADDED
	string tableName = p->tables[0];
	vector<LogicExpression::ExpressionTree*> expTree = p->trees;

	Table * table = findTable(tableName);

	if (table == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	Column * column = table->findColumn(columnName);

	if (column == NULL) {
		throw DatabaseException(20, columnName + " does not exist.");
	}

	string colType = column->getColumnType();
	if (colType != "int" && colType != "float") {
		throw DatabaseException(24,
				columnName + " must be of type int or float");
	}

	vector<string> columnNames = table->columnNames();

	double outlier = 0.0;
	if(!min)
		outlier=-2000000;
	else
		outlier=2000000;
	int colIndex = -1;

	for (int i = 0; i < columnNames.size(); i++) {
		if (columnNames[i] == columnName) {
			colIndex = i;
			break;
		}
	}

	//Loop through the rows.
	//If each row passes the test, then remove it from the table
	for (int i = 0; i < table->rowCount(); i++) {

		vector<string> thisRow = table->getRow(i);

		//Make sure the row passes each exression
		bool rowPasses = false;
		for (int k = 0; k < expTree.size(); k++) {
			//FIXX: IS THIS RIGHT?
			rowPasses = expTree[k]->isTrue(columnNames, thisRow);
			if (!rowPasses) {
				break;
			}
		}

		//If there's not comparators, then it auto passes!
		if (expTree.size() == 0) {
			rowPasses = true;
		}

		//Now if they used the AS operator, then we need to
		//assign the values to the new column names
		if (rowPasses) {
			float val = atof(thisRow[colIndex].c_str());
			if (min) {
				if (outlier > val) {
					outlier = val;
				}
			} else {
				if (outlier < val) {
					outlier = val;
				}
			}
		}
	}

	return outlier;
}

/*
 Count the number of rows
*/
int Database::countStatement(Query_parser* p) {
	string tableName = p->tables[0];
	vector<LogicExpression::ExpressionTree*> expTree = p->trees;

	Table * table = findTable(tableName);

	if (table == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	vector<string> columnNames = table->columnNames();
	int count = 0;

	//Loop through the rows.
	//If each row passes the test, then remove it from the table
	for (int i = 0; i < table->rowCount(); i++) {

		vector<string> thisRow = table->getRow(i);

		//Make sure the row passes each exression
		bool rowPasses = false;
		for (int k = 0; k < expTree.size(); k++) {
			//FIXX: IS THIS RIGHT?
			rowPasses = expTree[k]->isTrue(columnNames, thisRow);
			if (!rowPasses) {
				break;
			}
		}

		//If there's not comparators, then it auto passes!
		if (expTree.size() == 0) {
			rowPasses = true;
		}

		//Now if they used the AS operator, then we need to
		//assign the values to the new column names
		if (rowPasses) {
			count++;
		}
	}

	return count;
}

/*
 Same as queryParsing, but updates the row if it passes with new values
*/
void Database::updateParsing(Query_parser* p, vector<string> columnNames,
		vector<string> columnData, string tableName) {
	vector<LogicExpression::ExpressionTree*> expTree = p->trees;
	Table * table = findTable(tableName);

	if (table == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}
	vector<string> TableColumnNames = table->columnNames();
	//Loop through the rows.
	//If each row passes the test, then remove it from the table
	for (int i = 0; i < table->rowCount(); i++) {
		vector<string> thisRow = table->getRow(i);

		//Make sure the row passes each exression
		bool rowPasses = false;
		for (int k = 0; k < expTree.size(); k++) {
			//FIXX: IS THIS RIGHT?
			rowPasses = expTree[k]->isTrue(TableColumnNames, thisRow);
			if (!rowPasses) {
				break;
			}
		}

		//If there's not comparators, then it auto passes!
		if (expTree.size() == 0) {
			rowPasses = true;
		}

		//Now if they used the AS operator, then we need to
		//assign the values to the new column names
		if (rowPasses) {
			table->updateRow(i, columnNames, columnData);
		}
	}
}

/*
 this is given the partial tables that are returned by the query
 it is also given the columns that are joined
 it will go through all the joined column pairs
 for each pair it will find all of the matching rows
 for each matching row it will combine them
 for each row that is not in both it will add it to the end
*/
void Database::combineTables(vector<Table*> tables, Query_parser* parser,
		Table* into) {

	//tables should have the wored partial on it
	for (int k = 0; k < tables.size(); k++) {
		if (tables[k] == NULL) {
			throw DatabaseException(10, "NULL TABLE does not exist.");
		}
		string name = tables[k]->getTableName();
		name = name.substr(7, name.length());
	}
	
	vector<string> combines = parser->join_columns;
	for (int k = 0; k < combines.size(); k += 2) {
		vector<string> pairOne = globalParse::get_separate_statments(
				combines[k], ".");
		vector<string> pairTwo = globalParse::get_separate_statments(
				combines[k + 1], ".");
		if(debug)
		{
			cout<<"OTHER TABLES IS "<<"partial" + pairOne[0]<<"partial" + pairTwo[0]<<endl;
		}
		Table* table1 = findTable("partial" + pairOne[0]);
		Table* table2 = findTable("partial" + pairTwo[0]);
		if (table1 == NULL) {
			throw DatabaseException(10, pairOne[0] + " does not exist.");
		}
		if (table2 == NULL) {
			throw DatabaseException(10, pairTwo[0] + " does not exist.");
		}
		//tables are not null

		string column1Name = parser->short_name_new_columns[pairOne[1]];
		string column2Name = parser->short_name_new_columns[pairTwo[1]];
	//	cout<<"THESE ARE "<<column1Name<<" "<<pairOne[1]<<endl;


	//	cout<<"THESE ARE "<<column2Name<<" "<<pairTwo[1]<<endl;
		Column* col1;
		if(table1->findColumn(column1Name)==NULL||column1Name==""||column1Name==" ")
		{
	//		cout<<"FIND COLUMN "<<pairOne[1]<<table1->getTableName()<<" "<<combines[k]<<endl;
			col1=findColumn(combines[k]);
		}else
		{
			col1 = table1->findColumn(column1Name);
		}
		Column* col2;
		if(table2->findColumn(column2Name)==NULL||column2Name==""||column1Name==" ")
		{
	//		cout<<"FIND COLUMN "<<pairTwo[1]<<table2->getTableName()<<" "<<combines[k+1]<<endl;
			col2=findColumn(combines[k+1]);
		}else
		{
			col2=table2->findColumn(column2Name);
		}
		if (col1 == NULL) {
			throw DatabaseException(20, column1Name + " does not exist.");
		}
		if (col2 == NULL) {
			throw DatabaseException(20, column2Name + " does not exist.");
		}

		//columns are not null
		if (col1->getColumnType() != col2->getColumnType()) {
			if (tables[k] == NULL) {
				throw DatabaseException(
						13,
						pairOne[1] + " must have the same type as "
								+ pairTwo[1]);
			}
		}
		
		//this will combine the columns into a kinda new table
		//so that it will only loop through the rows
		map<string, Column*> columnNameToColumn;
		//this will be a map that determines whether it is the first table or second
		//true=first, false=second
		map<string, bool> firstOrSecond;
		vector<string> names = into->columnNames();
		for (int nameCount = 0; nameCount < names.size(); nameCount++) {
			string name = names[nameCount];
			Column* table1column = table1->findColumn(name);
			Column* table2column = table2->findColumn(name);
			if (table1column != NULL && table2column != NULL) {
				continue;
			}
			if (table1column != NULL) {
				columnNameToColumn[names[nameCount]] = table1column;
				firstOrSecond[name] = true;
			}
			if (table2column != NULL) {
				columnNameToColumn[names[nameCount]] = table2column;
				firstOrSecond[name] = false;
			}
		}

		map<int, bool> matchedrows;
		//goes through and finds matching rows
		for (int col1C = 0; col1C < col1->rowCount(); col1C++) {
			string value = col1->getValueAtRowIndex(col1C);
			bool matched = false;
			for (int col2C = 0; col2C < col2->rowCount(); col2C++) {
				string value2 = col2->getValueAtRowIndex(col2C);
				if (value == value2) {
					matched = true;
					matchedrows[col2C] = true;
					vector<string> rowdata;
					//We need to combine them now
					for (int nameCount = 0; nameCount < names.size();
							nameCount++) {
						if(debug)
						{
							cout<<names[nameCount]<<endl;
						}
						string name = names[nameCount];
						string data;
						if (name != column1Name) {
							//get the column with the same name  if it is the first get at one index else the other
							int index = firstOrSecond[name] ? col1C : col2C;
							data = columnNameToColumn[name]->getValueAtRowIndex(
									index);

						} else {
							data = value;
						}
						if(debug)
						{
							cout<<"PUSHING BACK "<<data<<endl;
						}
						rowdata.push_back(data);
					}
					into->addRow(names, rowdata);
				} else {

					if (!matchedrows[col2C]) {
						//just to make sure it is set
						matchedrows[col2C] = false;
					}
				}
			}
			if (!matched) {
				vector<string> rowdata;
				for (int nameCount = 0; nameCount < names.size(); nameCount++) {

					string name = names[nameCount];
					//get the column with the same name  if it is the first get at one index else the other
					string data = "";
					if (name == column1Name) {
						data = value;
					} else if (firstOrSecond[name]) {
						data = columnNameToColumn[name]->getValueAtRowIndex(
								col1C);
					} else {
						//leet for default  (it is so that it wont be confused as an actual value)
						data = "D3FAL7";
					}
					if(debug)
					{
						cout<<"PUSHING BACK "<<data<<endl;
					}
					rowdata.push_back(data);
				}

				into->addRow(names, rowdata);
				//left side has one that is not in right side
			}
		}
		map<int, bool>::iterator it;
		for (it = matchedrows.begin(); it != matchedrows.end(); it++) {
			if (!(*it).second) {
				//the right side had one that is not in the left side
				vector<string> rowdata;
				for (int nameCount = 0; nameCount < names.size(); nameCount++) {
					string name = names[nameCount];
					//get the column with the same name  if it is the first get at one index else the other
					string data = "";
					if (name == column2Name) {
						data = col2->getValueAtRowIndex((*it).first);
					} else if (!firstOrSecond[name]) {
						data = columnNameToColumn[name]->getValueAtRowIndex(
								(*it).first);
					} else {
						data = "D3FAL7"; //leet for default  (it is so that it wont be confused as an actual value)
					}
					if(debug)
					{
						cout<<"PUSHING BACK "<<data<<endl;
					}
					rowdata.push_back(data);
				}
				into->addRow(names, rowdata);
			}
		}

	}

	if(debug)
	{
		cerr<<into->printSelf()<<endl;
	}
	//these tables should have items that match up
	//they should actually be in pairs of two!!
	//also they are in order with the table name
}

/*
 Set the Primary Key for a table given the table name and given the column name
*/
void Database::setPrimaryKey(string tableName, string colName) {
	Table *theTable = findTable(tableName);

	if (theTable == NULL) {
		throw DatabaseException(10, tableName + " does not exist.");
	}

	theTable->setPrimaryKey(colName);
}

/*
 Return all the tables data
*/
string Database::printAllTables() {
	string s = "";
	map<string, Table*>::iterator it;
	for (it = tableList.begin(); it != tableList.end(); it++) {
		if (findTable((*it).first) != NULL)
			s += printTable((*it).first);
	}
	return s;
}

void Database::setDebug(bool input)
{
	debug = input;
}
