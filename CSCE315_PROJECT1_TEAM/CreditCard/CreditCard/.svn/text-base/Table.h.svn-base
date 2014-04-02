#ifndef _TABLE_H_
#define _TABLE_H_

#include "Item.h"
#include <unordered_map>
#include <queue>

//forward declare Database for where evaluation
class Database;

class Table {
private:
	string tableName;
	unordered_map<string, int> attributeNames;
	unordered_map<string, ItemBase::Type> dataTypes;
	unordered_map<string, bool> primaryKeys;
	vector<vector<ItemBase*>> dataRecords;

	//done
	bool EvaluateSubExpression(string subExpression, vector<ItemBase*> record,
			vector<Table>& tables);

	// done
	void InsertTuple(vector<ItemBase*> items);

	// done
	void InsertSingleItem(int row, ItemBase* item);

public:
	// done
	Table(string newTableName);

	// done
	void AddAttributeAndType(string dataType, string attributeName);

	// done
	void AddPrimaryKey(string attributeName);

	// done
	short InsertTuple(string tupleValues);

	// done
	string GetTableName();

	// done
	string GetAttributeName(int attribIndex);

	// done
	void deleteRecord(int i);

	// done
	queue<string> WhereToPostFix(string expression);

	// done
	bool EvaluateWherePostfix(queue<string> postfix, int whichRecord,
			vector<Table>& tables);

	// done
	void PrintTable();

	// done
	void PrintAttributes();

	// done
	ItemBase::Type AttributeType(string attributeName);

	// done
	int Count();

	// done
	int GetAttributeCount();

	// done
	double Sum(string attribute);

	// done
	void Min(string attribute, Table& targetTable);

	// done
	void Max(string attribute, Table& targetTable);

	// done
	void AppendAnotherTable(Table& tableToAdd);

	// done
	void DeleteColumn(string attributeName);

	// done
	void ChangeAttributeName(string oldName, string newName);

	// done
	void SetTableName(string newName);

	// done
	short ChangeValue(string value, string attribute, int index);

	// done
	bool IsPrimaryKey(string attributeName);

	// done
	template<class T>
	bool In(string attribute, T value);

	friend class Table;
};

// done
template<class T>
bool Table::In(string attributeName, T value) {
	unordered_map<string, int>::iterator iter = attributeNames.begin(); // this table should be 1 column
	bool result;
	ItemBase* attributeValue;
	int i = 0;

	for (; iter != attributeNames.end(); iter++) {
		if ((*iter).first == attributeName) {
			for (int j = 0; j < dataRecords.size(); j++) {
				attributeValue = dataRecords[j][i];
				result = (value == ((Item<T>*) attributeValue)->GetData());

				if (result == true) { // values match, dont continue searching
					break;
				}
			}
		} else { // specified attribute does not exist in the table
			result = false;
		}

		if (result == true) { // values match, dont continue searching
			break;
		}

		i++;
	}

	return result;
}

#endif
