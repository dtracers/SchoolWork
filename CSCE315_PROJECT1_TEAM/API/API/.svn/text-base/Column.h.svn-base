#ifndef __Column_H_
#define __Column_H_

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "Date.h"
#include "Time.h"

using namespace std;

class Column
{
public:
	Column(string type); 
	~Column(void);

	string getColType(){ return colType;}
	int getVarCharMaxLength(){ return varcharMaxLength;}
	int rowCount();
	void addRow(string val);
	void setPrimary(bool p) { isPrimary = p; }
	bool isPrimaryKey() { return isPrimary; }
	bool valExists(string val);
	string printDataList();
	string getValueAtRowIndex(int rowIndex);
	string getColumnType(){ return colType; }

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
