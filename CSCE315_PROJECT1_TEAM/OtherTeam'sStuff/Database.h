#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <string>
#include "Table.h"

#define SUCCESS				 0
#define	INVALID_INPUT		 1
#define	TYPE_CONVERSION		 2
#define INVALID_TABLE        3
#define	INVALID_ATTRIBUTE	 4
#define	NO_PRIMARY_KEY       5
#define	NAME_EXISTS          6

#define dllExport __declspec(dllexport)

using namespace std;

class dllExport Database{
private:
	vector<Table> tables;	

public:
	short IssueCommand(string input);
	short Create(string input);
	short Modify(string input);
	short Query(string input);
	short Delete(string input);
	short Print(string input);
};
#endif





