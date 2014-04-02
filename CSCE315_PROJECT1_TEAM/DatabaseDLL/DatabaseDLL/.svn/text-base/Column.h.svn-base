/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The header file for the Column class
*/
#ifndef __Column_H_
#define __Column_H_

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "Date.h"
#include "Time.h"

using namespace std;

class Column {
public:
	Column(string type);
	~Column(void);

	int getVarCharMaxLength() {
		return varcharMaxLength;
	}
	int rowCount();
	void addRow(string val, int editRowIndex = -1);
	void deleteRow(int rowIndex);
	void setPrimary(bool p) {
		isPrimary = p;
	}
	bool isPrimaryKey() {
		return isPrimary;
	}
	bool valExists(string val);
	bool valValid(string val);
	string printDataList();
	string getValueAtRowIndex(int rowIndex);
	string getColumnType() {
		return colType;
	}

private:
	vector<int> intList;
	vector<float> floatList;
	vector<string> varcharList;
	vector<Date *> dateList;
	vector<Time *> timeList;

	string colType;
	int varcharMaxLength;
	bool isPrimary;
};

#endif
