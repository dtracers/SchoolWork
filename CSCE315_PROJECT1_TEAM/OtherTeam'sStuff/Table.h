#ifndef _TABLE_H_
#define _TABLE_H_

#include "Tuple.h"

class Table {
private:
   string tableName;
	vector<string> attributeNames;
   vector<ItemBase::Type> dataTypes;
   vector<Tuple> dataTuples;
public:
	Table(string newTableName);

   // add one attribute and its type at a time
   short AddAttributeAndType(string dataType, string attributeName);

   // add a tuple, input is a string with the values in order with a space between them
	short InsertTuple(string tupleValues);

   // returns the table name
   string GetTableName();

   // prints a table
   void PrintTable();
};
#endif
