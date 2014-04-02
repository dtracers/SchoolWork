/*
 Database API for Team 4
 Authors: Ben Beadle, Amanda Cofsky, David Turner

 The exception class that contains default values for all exceptions
 Learn more at http://goo.gl/lTVVA
*/
#ifndef __DatabaseException_H_
#define __DatabaseException_H_

#include <exception>
#include <iostream>
using namespace std;

class DatabaseException: public exception {

public:
	DatabaseException(int c, string m = "") {
		code = c;

		string vagueExplanation;

		switch (code) {
		case 10:
			title = "TableDoesNotExist";
			vagueExplanation = "Table does not exist.";
			break;
		case 11:
			title = "TableExists";
			vagueExplanation = "Table already exist.";
			break;
		case 12:
			title = "VectorSizeMismatch";
			vagueExplanation =
					"columnNames vector and rowData vector size mismatch.";
			break;
		case 15:
			title = "InvalidColumnName";
			vagueExplanation = "Column Name is not valid.";
			break;
		case 16:
			title = "InvalidInsertStatement";
			vagueExplanation = "Insert statement is not valid.";
			break;
		case 17:
			title = "InvalidDeleteStatement";
			vagueExplanation = "Delete statement is not valid.";
			break;
		case 18:
			title = "InvalidWhereClause";
			vagueExplanation = "Where clause is not not a valid format.";
			break;
		case 19:
			title = "InvalidUpdateStatement";
			vagueExplanation = "Update statement is not valid.";
			break;
		case 20:
			title = "ColumnDoesNotExist";
			vagueExplanation = "Column does not exist.";
			break;
		case 21:
			title = "ColumnExistsException";
			vagueExplanation = "Column already exists.";
			break;
		case 22:
			title = "PrimaryKeyValueExists";
			vagueExplanation = "Primary Key value already exists.";
			break;
		case 23:
			title = "InvalidFromClause";
			vagueExplanation = "From clause is not a valid format.";
			break;
		case 24:
			title = "ColumnTypeNotIntOrFloat";
			vagueExplanation = "Column Type must be int or float.";
			break;
		case 25:
			title = "InvalidSelectClause";
			vagueExplanation = "Select clause is not a valid format.";
			break;
		case 26:
			title = "InvalidSelectFunctionColumnType";
			vagueExplanation = "Select clause Column Type is not valid.";
			break;
		case 30:
			title = "ColumnTypeDoesNotExist";
			vagueExplanation = "Not a valid Type.";
			break;
		case 31:
			title = "VarcharLengthTooShort";
			vagueExplanation = "Length cannot be less than or equal to zero.";
			break;
		case 32:
			title = "VarcharLengthTooLong";
			vagueExplanation = "Length cannot be greater than 100.";
			break;
		case 33:
			title = "InvalidInteger";
			vagueExplanation = "String was not successfully converted to int.";
			break;
		case 34:
			title = "InvalidFloat";
			vagueExplanation =
					"String was not successfully converted to float.";
			break;
		case 35:
			title = "VarcharTooLong";
			vagueExplanation =
					"Varchar is too big to fit in specific max length.";
			break;
		case 40:
			title = "InvalidDate";
			vagueExplanation = "Date given is not a valid date.";
			break;
		case 41:
			title = "InvalidTime";
			vagueExplanation = "Time given is not a valid time.";
			break;
		case 50:
			title = "MismatchedParathesis";
			vagueExplanation = "parentheses are mismatched.";
			break;
		default:
			msg = title = "Unknown";
			vagueExplanation = "Unknown Exception";
			break;
		}
		if (m.compare("") != 0) {
			msg = m;
		} else {
			msg = vagueExplanation;
		}
	}
	~DatabaseException() throw () {
	}
	const char *getMessage() {
		return msg.c_str();
	}
	const char *getTitle() {
		return title.c_str();
	}
	const int getCode() {
		return code;
	}

private:
	int code;
	string title;
	string msg;
};

inline std::ostream& operator<<(std::ostream& out, DatabaseException& e) {
	out << e.getTitle() << " (" << e.getCode() << "): " << e.getMessage()
			<< endl;
	return out;
}

#endif
