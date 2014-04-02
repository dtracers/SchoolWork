/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The header file for the middle-man class
*/

#ifndef __FUNCTIONALDATABASEDLL_H_
#define __FUNCTIONALDATABASEDLL_H_

#include "DatabaseDLL.h"
#include "Database.h"
#include<iostream>
#include<fstream>


class FunctionalDatabaseDLL: public DatabaseDLL {
public:
	bool debug;
	Database* db;

	ofstream outfile;
	FunctionalDatabaseDLL();
	int create(string input);
	int deleteRows(string input);
	int drop(string tableName);
	string getErrorMessage();
	int insert(string input);
	string list(string tableName);
	string query(string input);
	int recordCount(string tableName = "");
	int update(string input);
	void setDebug(bool input);
	~FunctionalDatabaseDLL();
};

#endif /* FUNCTIONALDATABASEDLL_H_ */
