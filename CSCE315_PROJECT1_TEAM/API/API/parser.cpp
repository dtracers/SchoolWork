/*
 * parser.cpp
 *
 *  Created on: Jan 31, 2012
 *      Author: gigemjt
 */

#include "parser.h"
#include "Database.h"
#include "Query_parser.h"
parser::parser(Database* DB) {
	db=DB;
}
void parser::parse(string g)
{
	int old_index=0;
	int instruction_index=g.find_first_of(';');
	while(instruction_index>=0)
	{
		string instruction=g.substr(old_index,instruction_index-old_index);
		find_command(instruction);
		cout<<"\n\n\n\n"<<endl;
		old_index=instruction_index+1;
		instruction_index=g.find_first_of(';',old_index);
		//cerr<<"the insex is "<<old_index<<" length is "<<g.length()<<"\n";
	}
	db->printAllTables();
}
void parser::find_command(string command)
{
	stringstream stream(command);
	string first_word,second_word;
	stream>>first_word;
	stream>>second_word;
	//from these two the command type should be able to be found


	//FIRST COMMAND !!!!
	if(first_word=="CREATE"&&second_word=="TABLE")
	{
		cout<<"THE COMMAND IS CREATING TABLE"<<endl;
		Table_parser crc(db);
		crc.create_table(command);
	}
	if(first_word=="SELECT")
	{
		cout<<"THE COMMAND IS QUERYING TABLE"<<endl;
		Query_parser crc(command,db);
	}
	if(first_word=="INSERT"&&second_word=="INTO")
	{
		cout<<"THE COMMAND IS INSERTING"<<endl;
		Table_parser crc(db);
		crc.insert(command);
	}
}
parser::~parser() {
	// TODO Auto-generated destructor stub
}
