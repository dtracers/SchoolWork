/*
	Database API for Team 4
	Authors: Ben Beadle, Amanda Cofsky, David Turner

	The following virtual functions are ones you can use through API calls.
	Learn more at http://goo.gl/lTVVA
*/

#include <iostream>
using namespace std;

class Database {
    static __declspec(dllexport) Database* createDatabase();
	virtual __declspec(dllexport) int create(string input) = 0;
	virtual __declspec(dllexport) int deleteRows(string input) = 0;
	virtual __declspec(dllexport) int drop(string tableName) = 0;
	virtual __declspec(dllexport) string getErrorMessage() = 0;
	virtual __declspec(dllexport) int insert(string input) = 0;
	virtual __declspec(dllexport) string list(string tableName) = 0;
	virtual __declspec(dllexport) string query(string input) = 0;
	virtual __declspec(dllexport) int recordCount(string tableName = "") = 0;
	virtual __declspec(dllexport) int update(string input) = 0;
};