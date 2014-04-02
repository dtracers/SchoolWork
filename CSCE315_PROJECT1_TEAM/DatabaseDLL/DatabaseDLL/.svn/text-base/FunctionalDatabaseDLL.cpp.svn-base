/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The database class we use that interacts with the user.
 This class is a middleman between the user and the Database class.
 The methods simply try and catch the Database methods.
 
 Learn more at http://goo.gl/lTVVA
*/
#include "FunctionalDatabaseDLL.h"
#include<fstream>

FunctionalDatabaseDLL::FunctionalDatabaseDLL() {
	db=new Database();
	debug=false;
	string file = "debugout.txt";
	outfile.open(file.c_str());
}

FunctionalDatabaseDLL::~FunctionalDatabaseDLL() {
	delete db;
}

int FunctionalDatabaseDLL::create(string input)
{
	try {
		outfile<<input<<"/n";
		db->create(input);
	} catch(DatabaseException& e) {
		db->setErrorMessage(e.getMessage());
		if(debug) {
			cout << "ERROR (create): " << e.getMessage() << endl;
		}
		return e.getCode();
	}

	return 0;
}

int FunctionalDatabaseDLL::deleteRows(string input)
{
	try {
		outfile<<input<<"\n";
		db->deleteRows(input);
	} catch(DatabaseException& e) {
		db->setErrorMessage(e.getMessage());
		if(debug) {
			cout << "ERROR (create): " << e.getMessage() << endl;
		}
		return e.getCode();
	}

	return 0;
}

int FunctionalDatabaseDLL::drop(string tableName)
{
	try {
		db->drop(tableName);
	} catch(DatabaseException& e) {
		db->setErrorMessage(e.getMessage());
		if(debug) {
			cout << "ERROR (create): " << e.getMessage() << endl;
		}
		return e.getCode();
	}

	return 0;
}

string FunctionalDatabaseDLL::getErrorMessage()
{
	return db->getErrorMessage();
}

int FunctionalDatabaseDLL::insert(string input)
{
	try {
		outfile<<input<<"\n";
		db->insert(input);
	} catch(DatabaseException& e) {
		db->setErrorMessage(e.getMessage());
		if(debug) {
			cout << "ERROR (create): " << e.getMessage()<<"\n";
		}
		return e.getCode();
	}

	return 0;
}

string FunctionalDatabaseDLL::list(string tableName)
{
	try
	{
		return db->list(tableName);
	} catch(DatabaseException& e) {
		db->setErrorMessage(e.getMessage());
		if(debug) {
			cout << "ERROR (create): " << e.getMessage() << endl;
		}
		return "An error was thrown.  Call getErrorMessage() for details";
	}
}

string FunctionalDatabaseDLL::query(string input)
{
	try {
		outfile<<input<<"\n";
		return db->query(input);
	} catch(DatabaseException& e) {
		db->setErrorMessage(e.getMessage());
		if(debug) {
			cout << "ERROR (create): " << e.getMessage() << endl;
		}
		return "An error was thrown.  Call getErrorMessage() for details";
	}
}

int FunctionalDatabaseDLL::recordCount(string tableName)
{
	try {
		db->recordCount(tableName);
	} catch(DatabaseException& e) {
		db->setErrorMessage(e.getMessage());
		if(debug) {
			cout << "ERROR (create): " << e.getMessage() << endl;
		}
		return e.getCode();
	}
	return 0;
}

int FunctionalDatabaseDLL::update(string input)
{
	try {
	outfile<<input<<"\n";
		db->update(input);
	} catch(DatabaseException& e) {
		db->setErrorMessage(e.getMessage());
		if(debug) {
			cout << "ERROR (create): " << e.getMessage() << endl;
		}
		return e.getCode();
	}

	return 0;
}

void FunctionalDatabaseDLL::setDebug(bool input)
{
	debug=input;
	if(debug)
	{
		cout<<"DEBUGGING IS NOW TURNED ON"<<endl;
	}
	db->setDebug(input);
}
