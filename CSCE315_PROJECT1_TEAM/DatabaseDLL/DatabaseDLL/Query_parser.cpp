/*
 * Query_parser.cpp
 *
 *  Created on: Jan 31, 2012
 *      Author: gigemjt
 */

#include "Query_parser.h"
#include "global_parsing_methods.h"

Query_parser::Query_parser(Database* DB) {
	db = DB;

	//after it has all the data in a non single way it will do actions here
}

/**
 * Parses the query then calls action
 */
void Query_parser::parse(string g) {
	parse_query(g);
	action();
}
/**
 * This will parse the main file
 */

/**
 *
 */
void Query_parser::deleteRows(string g) {
	stringstream stream(g);
	string pre_junk;
	stream >> pre_junk;
	stream >> pre_junk;
	string table_name;
	stream >> table_name;
	tables.push_back(table_name);
	Table* table = db->findTable(table_name);
	int other=g.find("WHERE");
	if (other > 0) {
		where_parser(g);
		db->deleteParsing(this);
	} else {
		table->deleteAllRows();
	}
}

void Query_parser::parse_query(string g) {
	//cout << " the total string " << g << endl;
	int select_index = g.find_first_of("SELECT");
	int from_index = g.find("FROM");

	//this will search after the select index
	int sub_select = g.find("SELECT", from_index);
	if (sub_select > 0) {
		//there is a sub query!! so exciting
		string search = g.substr(select_index, sub_select - select_index);
		int start_parenth = search.find_last_of("("); //this should find the last one

		//this will find the closing parenthesis
		int count = 1;
		int index = start_parenth;
		while (index < g.length() && count > 0) {
			if (g[index] == '(')
				count++;
			if (g[index] == ')')
				count--;
			index++;
		}
		if (count == 0)
			index--;
		string sub_query = g.substr(start_parenth + 1,
				index - (start_parenth + 2));
		Query_parser sub_qrp(db);
		sub_qrp.parse(sub_query);
		//it will have other things like a table name and a dot "."
		string substitute = sub_qrp.get_single_selections();
		string first = g.substr(0, start_parenth);
		string second = g.substr(index, g.length());
		g = first + substitute + second;
//		cout << "MY NEW STRING IS " << g << endl;
	}
	int store_index = g.find("STORE");
	if (store_index < 0) {
		//	cerr<<"store doesnt exist\n "<<store_index<<endl;;
		store_index = g.length();
	}
//	cout<<"from_index "<<from_index<<"endl";
	string select = g.substr(select_index, from_index - select_index);
	string from = g.substr(from_index, store_index - from_index);
	string store = g.substr(store_index, g.length() - store_index);
	select_parser(select);
	from_parser(from);
	store_parser(store);
}
/**
 * This will parse items just inside the select statement
 */
void Query_parser::select_parser(string statement) {
	all_columns = false;
//	cout<<"select statement "<<statement<<"\n";
	stringstream stream(statement);
	string pre_junk;
	stream >> pre_junk;
	string column;
	stream >> column;
	if (column == "*") {
//		cout<<"this will do ALL the columns\n";
		all_columns = true;
		return;
	}
	int pos = statement.find(column);
	int final_index = 0;
	while (pos > 0) {
		final_index = pos;
		int next = statement.find_first_of(',', pos);
		string data = "";
		for (int index = pos; index < next; index++) {
			data += statement[index];
		}
		//this will parse a single selection
		single_selection(data);
		pos = next + 1;
	}
	string data = "";
	int last_index = statement.length();
	for (int index = final_index; index < last_index; index++) {
		data += statement[index];
	}
	single_selection(data);
}

/**
 * This will evalutate all statments
 */
void Query_parser::single_selection(string g) {
	if (g.length() < 1)
		return;
	//it should be changed so that the line after the AS statement gets put here
	int AS = g.find("AS");
	string new_column_name;
	string old_column_name;

	//this will get the first name which is the old column name
	stringstream stream(g);
	stream >> old_column_name; //may not be that way
	if (AS > 0) {
		//the AS statement exist
		string new_name = g.substr(AS, g.length());
		stringstream stream(new_name);
		string pre_junk;
		stream >> pre_junk;
//		cout<<"pre_junk = AS? : "<<pre_junk<<"\n";
		stream >> new_column_name;
	} else {
		//if the as statement doesn't exist then the new column name is the old column name
		new_column_name = old_column_name;
	}
	old_columns.push_back(old_column_name);
	new_columns[old_column_name] = new_column_name;
	vector<string> sep = globalParse::get_separate_statments(old_column_name,
			".");
	cout<<sep[sep.size() - 1]<<"is now "<<new_column_name<<endl;
	short_name_new_columns[sep[sep.size() - 1]] = new_column_name;
//	cout<<"new column name is "<<new_column_name<<"\n";
//	cout<<"old column name is "<<old_column_name<<"\n";
}

/**
 * This will return all of the tables that were in the result of the query
 */
string Query_parser::get_single_selections() {
	string select = "";
	for (int k = 0; k < old_columns.size(); k++) {
		string after = "";
		if (k < old_columns.size() - 1)
			after = ", ";
		select += new_columns[old_columns[k]] + after;
	}
	return select;
}

int Query_parser::selectFunctionsExist() {

	int functionCount = 0;
	int currentColumn = 0;

	map<string, string>::iterator oldToNewColumnsIt;
	vector<string> deletes;
	for (oldToNewColumnsIt = new_columns.begin();
			oldToNewColumnsIt != new_columns.end(); oldToNewColumnsIt++) {

		string str = oldToNewColumnsIt->first;
		string str2 = new_columns[str];
//		cout<<"exist? "<<str<<"="<<str2<<endl;
		if (str2 == "") {
			deletes.push_back(str);
			continue;
			//it is fake
		}
		bool exist = str.find("SUM") != string::npos
				|| str.find("COUNT") != string::npos
				|| str.find("MIN") != string::npos
				|| str.find("MAX") != string::npos;

		//Set result to 1 as long as the previous columsn have functions
		if (exist) {
			//Not all values include select functions
			if (currentColumn != 0 && functionCount == 0) {
				return -1;
			}
			functionCount++;
		} else {
			if (functionCount > 0) {
				return -1;
			}
		}
		currentColumn++;
	}
	for (int k = 0; k < deletes.size(); k++) {
		oldToNewColumnsIt = new_columns.find(deletes[k]);
		new_columns.erase(oldToNewColumnsIt);
	}
	return functionCount;
}

string Query_parser::selectFunctionRemove(string input) {
	if (input.find("SUM") != string::npos) {
		input = input.substr(4, input.length() - 5);
	} else if (input.find("COUNT") != string::npos) {
		input = input.substr(6, input.length() - 7);
	} else if (input.find("MIN") != string::npos) {
		input = input.substr(4, input.length() - 5);
	} else if (input.find("MAX") != string::npos) {
		input = input.substr(4, input.length() - 5);
	}
	return input;
}

void Query_parser::from_parser(string g) {
	//DAVID: WE DON'T NEED TO IMPLEMENT GROUP AND ORDER BY.
	//WHOEVER PUT THIS: GOOD THING I DIDNT :P
	int group = g.find("GROUP");
	if (group >= 0) {
		group_by(g.substr(group, g.length() - group));
		g = g.substr(0, group);
	}
	int order = g.find("ORDER");
	if (order >= 0) {
		order_by(g.substr(order, g.length() - order));
		g = g.substr(0, order);
	}
	int where_conditional = g.find("WHERE");
	string table_part = g;
	if (where_conditional >= 0) {
		where_parser(
				g.substr(where_conditional, g.length() - where_conditional));
		table_part = g.substr(0, where_conditional);
	}
	stringstream stream(table_part);
	string pre_junk;
	stream >> pre_junk;
	table_part = table_part.substr(table_part.find(pre_junk) + pre_junk.size(),
			table_part.size());
	vector<string> joins = globalParse::get_separate_statments(table_part, ",");
	for (int k = 0; k < joins.size(); k++) {
		table_parser(joins[k]);
	}

}

void Query_parser::order_by(string g) {
	//order here
	cout << "order statement " << g << endl;
}
void Query_parser::group_by(string g) {
	cout << "group statement " << g << endl;
}
void Query_parser::where_parser(string g) {
//	cerr<<"WHERE IS "<<g<<endl;
	int where = g.find("WHERE");
	g = g.substr(where + 5, where + 5 - g.length());
	vector<string> split = globalParse::get_separate_statments(g, ",");
	for (int k = 0; k < split.size(); k++) {
		LogicHandler handle(split[k]);
		handle.parse();
		ExpressionTree* tree = handle.getTree();
		//tree->toString();
		trees.push_back(tree);
		tree->setDataBase(db);
	}
//	cout << "where statement " << g << "\n";
}

/**
 * format
 * table1
 * or
 * table1 JOIN tabel2 ON table1.column = table2.column
 */
void Query_parser::table_parser(string statement) {
//	cout<<"TABLE STATEMENT "<<statement<<endl;
	stringstream stream(statement);
	string pre_junk;

	string first_table;
	string end_of_line;

	stream >> first_table;
	tables.push_back(first_table);

	stream >> end_of_line;
//	cout << "end of line " << end_of_line << endl;
	if (statement.find(first_table) + first_table.size() < statement.size() - 1
			&& end_of_line != "") {
		string second_table;
		stream >> second_table;
//		cout << "there are more than books here" << endl;
		int on_pos = statement.find("ON");
		tables.push_back(second_table);
		if (on_pos > 0) {
			join_parser(statement.substr(on_pos, statement.length() - on_pos));
		}
	}
//	cout << "table statement " << statement << "\n";
}

void Query_parser::join_parser(string statement) {
//	cout << "JOIN STATEMENT IS????" << endl;
	stringstream stream(statement);
	string pre_junk;
	stream >> pre_junk;
	string first_half;
	stream >> first_half;
	string second_half;
	stream >> pre_junk; //should be =
	stream >> second_half;
//	cout << "first half is " << first_half << endl;
//	cout << "second half is " << second_half << endl;
	cout << "THE ON COMMAND IS " << statement << endl;
	join_columns.push_back(first_half);
	join_columns.push_back(second_half);
	//join_columns[first_bit[0]] = first_bit[1];
	//join_columns[second_bit[0]] = second_bit[1];
	//BABOOOOM!!!!!
}

/**
 * Parses a store function so they can save the table
 */
void Query_parser::store_parser(string g) {
	if (g.length() < 1) {
		static int temp_table_num;
		stringstream m;
		m << temp_table_num;
		temp_table_num++;
		string name_num;
		m >> name_num;
		new_table_name = "TEMP" + name_num;
//		cout << "the table being stored is " << new_table_name << endl;
		return;
	}
	stringstream stream(g);
	string pre_junk;
	stream >> pre_junk;
	string table_name;
	stream >> table_name;
//	cout << "the table being stored is " << table_name << endl;
	new_table_name = table_name;
}

/**
 * Creates a new table from the parse data
 * does not add any data or parse any queries
 */
void Query_parser::action() {
//	cout << "DONE PARSING NOW ACTING" << endl;
	if (all_columns) {
		for (int k = 0; k < tables.size(); k++) {
			Table * t = db->findTable(tables[k]);
			vector<string> names = t->columnNames();
			for (int i = 0; i < names.size(); i++) {
				old_columns.push_back(names[i]);
				new_columns[names[i]] = names[i];
			}
		}
	}
	Table* t = db->findTable(new_table_name);
	if (t == NULL) {
		db->createTable(new_table_name);
		t = db->findTable(new_table_name);
	}
	Table* t_old = db->findTable(tables[0]);

	for (int k = 0; k < old_columns.size(); k++) {
		string not_removed = old_columns[k];
		string removed = selectFunctionRemove(not_removed);
		bool diff = false;
		if (removed != not_removed) {
			diff = true;
		}
//		cout << "OLD C is " << not_removed;
//		cout << " removed" << removed << endl;
		Column* col;
		if (tables.size() == 1 || is_joined_column(removed)) {
//			cout<<"column name is "<<removed;
			col = t_old->findColumn(removed);
			if (col == NULL)
				throw DatabaseException(20, removed + " does not exist.");
		} else {
//			cout << "MORE THAN ONE TABLE" << endl;
//			cout << "NAME IS " << removed << endl;
			col = db->findColumn(removed);
//			cout << "DOES IT WORK?" << endl;
		}
		t->createColumn(new_columns[diff ? not_removed : removed], col);
	}
//	cout<<"PRE FINAL TABLE IS"<<endl;
	t->printSelf();
//	cout << "TO DB" << endl;
	db->completeQueryParsing(this);
}

bool Query_parser::is_joined_column(string column) {
	for (int k = 0; k < join_columns.size(); k++) {
		vector<string> full_name = globalParse::get_separate_statments(
				join_columns[k], ".");
		if (full_name[full_name.size() - 1] == column) {
			return true;
		}
	}
	return false;
}

Query_parser::~Query_parser() {
	// TODO Auto-generated destructor stub
}
