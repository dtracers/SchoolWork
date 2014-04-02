#include "Database.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Database db;
const int inputError = 7; // Error Code if User entered something wrong

// Error class
struct ApplicationException: public exception {
public:
	ApplicationException(int c) {
		code = c;
	}
	const int getCode() {
		return code;
	}
private:
	int code;
};

// Parse statements into a vector of strings
vector<string> get_separate_statments(string statement, string separator) {
	vector < string > sepa;
	int pos = 0;
	int final_index;
	while (pos >= 0) {
		final_index = pos;
		int next = statement.find(separator, pos);
		if (next > 0 && pos < statement.length()) {
			string data = statement.substr(pos, next - pos);
			sepa.push_back(data);
			pos = next + 1;
		} else {
			pos = -1;
		}
	}

	return sepa;
}

// Parse the statements and delete extra spaces
vector<string> parse(string input) {
	vector < string > parsedInput;

	parsedInput = get_separate_statments(input, ",");

	//Erase extra spaces in the front of words
	for (int i = 0; i < parsedInput.size(); i++) {
		if (parsedInput[i].at(0) == ' ') {
			parsedInput[i].erase(parsedInput[i].begin());
		}
	}

	return parsedInput;
}

// Used to insert transaction information into the table, format check where noted
void insert(vector<string> parsedInput) {
	int i = 0;
	while (i < parsedInput.size()) {
		string insertData = "";

		// Transaction Date
		insertData += parsedInput[i];
		insertData += ", ";
		i++;

		// Transaction Time
		insertData += parsedInput[i];
		insertData += ", ";
		i++;

		// Credit Card Number, checks if an 16 digit int, MUST NOT BE ZERO
		if (parsedInput[i].size() == 16 && atoi(parsedInput[i].c_str()) > 0) {
			insertData += parsedInput[i];
			insertData += ", ";
			i++;
		} else {
			throw ApplicationException(inputError);
		}

		// varchar Vender Name
		insertData += parsedInput[i];
		insertData += ", ";
		i++;

		// Transaction Amount, checks if a float, MUST NOT BE ZERO
		if (atof(parsedInput[i].c_str()) > 0) {
			insertData += parsedInput[i];
			insertData += ", ";
			i++;
		} else {
			throw ApplicationException(inputError);
		}

		// varchar Category
		insertData += parsedInput[i];
		insertData += ", ";
		i++;

		// varchar Vender Transaction id
		insertData += parsedInput[i];
		i++;

		// Finishes input string and inserts it
		insertData = "INSERT INTO Transactions VALUES (" + insertData + ")";
		int error = db.IssueCommand(insertData);
		if (error != 0) {
			throw ApplicationException(error);
		}
	}
}

int main()
try {

	int error = 0;
	int menuOption = 0;
	string userInput = "";
	string commandInput = "";

	// Creates Vendors, Users, and Transactions tables
	error =
			db.IssueCommand(
					"CREATE TABLE Vendors (storeName varchar(20), authorizationDate date, address varchar(100), storeType varchar(20))");
	if (error != 0) {
		throw ApplicationException(error);
	}
	error =
			db.IssueCommand(
					"CREATE TABLE Users (name varchar(20), accountNumber varchar(16), cardMemberDate date, creditBalance int)");
	if (error != 0) {
		throw ApplicationException(error);
	}
	error =
			db.IssueCommand(
					"CREATE TABLE Transactions (purchaseDate date, purchaseTime time, accountNumber varchar(16), purchasePlace varchar(100), amount float, purchaseType varchar(100), storeTransationID varchar(100))");
	if (error != 0) {
		throw ApplicationException(error);
	}

	// User Menu
	while (menuOption != 13) {
		cout << "What would you like to do?" << endl;
		cout << "1: Enter a new Vendor" << endl
				<< "2: Print the list of current Vendors" << endl
				<< "3: Enter a new User" << endl
				<< "4: Print the list of current Users" << endl
				<< "5: Enter a transaction file" << endl
				<< "6: Print the list of all Transactions" << endl
				<< "7: Generate monthly statement" << endl
				<< "8: Generate yearly statements" << endl
				<< "9: Generate transaction summary for vendor" << endl
				<< "10: Query about individual transactions" << endl
				<< "11: Query about transactions within a range of dates"
				<< endl
				<< "12: Query about transactions within a range of times"
				<< endl << "13: Exit" << endl;
		cin >> menuOption;

		switch (menuOption) {

		// Lets the user enter in a Vender manually through command line
		case 1: {
			cout
					<< "Please enter in values in the following format\n 'storeName, authorizationDate, address, storeType'"
					<< endl;
			cin.ignore(1);
			getline(cin, userInput);

			commandInput = "INSERT INTO Vendors VALUES (" + userInput + ")";

			error = db.IssueCommand(commandInput);
			if (error != 0) {
				throw ApplicationException(error);
			}

			commandInput = "";

			break;
		}

			// Prints the Vender table
		case 2: {
			error = db.IssueCommand("PRINT TABLE Vendors");
			if (error != 0) {
				throw ApplicationException(error);
			}

			break;
		}

			// Lets the user enter in a User manually through command line
		case 3: {
			cout
					<< "Please enter in values in the following format\n 'name, accountNumber, cardMemberDate, creditBalance'"
					<< endl;
			cin.ignore(1);
			getline(cin, userInput);

			commandInput = "INSERT INTO Users VALUES (" + userInput + ")";
			error = db.IssueCommand(commandInput);
			if (error != 0) {
				throw ApplicationException(error);
			}

			commandInput = "";
			break;
		}

			// Prints the User table
		case 4: {
			error = db.IssueCommand("PRINT TABLE Users");
			if (error != 0) {
				throw ApplicationException(error);
			}

			break;
		}

			// Reads transactions to add to the Transaction table from a file
		case 5: {
			string filename;
			string input;

			vector < string > parsedInput;

			cout << "Please enter in a filename." << endl;
			cin >> filename;

			//Read in from the given file
			ifstream ist(filename.c_str());
			if (!ist)
				runtime_error("Can't open input file");

			while (!ist.eof() && ist.good()) {
				string temp;
				getline(ist, temp, '\n');
				input += temp;
				input += ',';
			}

			//Parse the input into separate words in the parsedInput vector and insert it
			parsedInput = parse(input);
			insert(parsedInput);

			break;
		}

			// Print Transactions table
		case 6: {
			error = db.IssueCommand("PRINT TABLE Transactions");
			if (error != 0) {
				throw ApplicationException(error);
			}

			break;

		}

			// Uses a card number, month, and year to get a monthly statement
		case 7: {
			int month;
			int year;
			string dateStartingTransactions;
			string dateEndingTransactions;
			string cardIdNumber;

			cout
					<< "Please enter in the card number you would like a transaction summary of."
					<< endl;
			cin >> cardIdNumber;
			cout
					<< "Please enter in the month of transactions you would like to view."
					<< endl;
			cin >> month;
			cout << "Please enter in the year that you would like to view."
					<< endl;
			cin >> year;

			if (cardIdNumber.size() != 16 || atoi(cardIdNumber.c_str()) == 0) {
				throw ApplicationException(inputError);
			}

			// Get the range of dates (1st on one month to 1st of another)
			stringstream converter;
			converter << year << "/" << month << "/" << "01";
			dateStartingTransactions = converter.str();
			converter.str("");

			if (month + 1 == 12) {
				converter << year + 1 << "/01/01";
			} else {
				converter << year << "/" << month + 1 << "/" << "01";
			}
			dateEndingTransactions = converter.str();

			// Select all transactions between two dates with account number equal to a given number
			string input =
					"QUERY MonthlyTransactions SELECT * FROM Transactions WHERE ((purchaseDate >= "
							+ dateStartingTransactions
							+ ") AND (purchaseDate < " + dateEndingTransactions
							+ ") AND (accountNumber = " + cardIdNumber + "))";
			error = db.IssueCommand(input);
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("PRINT TABLE MonthlyTransactions");
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("DROP TABLE MonthlyTransactions");
			if (error != 0) {
				throw ApplicationException(error);
			}

			break;
		}

			//Uses a card number and a year to print a yearly statement
		case 8: {
			int year;
			string startingYear;
			string endingYear;
			string cardIdNumber;

			cout
					<< "Please enter in the card number you would like a transaction summary of."
					<< endl;
			cin >> cardIdNumber;
			cout << "Please enter in the year that you would like to view."
					<< endl;
			cin >> year;

			if (cardIdNumber.size() != 16 || atoi(cardIdNumber.c_str()) == 0) {
				throw ApplicationException(error);
			}

			//Used to determine the range of year
			stringstream converter;
			converter << year << "/" << "01" << "/" << "01";
			startingYear = converter.str();
			converter.str("");
			converter << year + 1 << "/" << "01" << "/" << "01";
			endingYear = converter.str();

			//Get all transactions between two years with a account number equal to the entered number
			string input =
					"QUERY YearlyTransactions SELECT * FROM Transactions WHERE ((purchaseDate >= "
							+ startingYear + ") AND (purchaseDate < "
							+ endingYear + ") AND (accountNumber = "
							+ cardIdNumber + "))";
			error = db.IssueCommand(input);
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("PRINT TABLE YearlyTransactions");
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("DROP TABLE YearlyTransactions");
			if (error != 0) {
				throw ApplicationException(error);
			}

			break;
		}

			// Show all transactions that occured at a given Vender
		case 9: {
			string venderName;
			cout << "Please enter in a vender's name." << endl;
			cin.ignore(1);
			getline(cin, venderName);

			string input =
					"QUERY VenderTransactions SELECT * FROM Transactions WHERE (purchasePlace = "
							+ venderName + ")";
			error = db.IssueCommand(input);
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("PRINT TABLE VenderTransactions");
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("DROP TABLE VenderTransactions");
			if (error != 0) {
				throw ApplicationException(error);
			}

			break;
		}

			// Uses a given date, time, and account number to get information about a specific transaction
		case 10: {
			string date;
			string time;
			string creditCardNumber;

			cout
					<< "Please enter in the date of the transaction in question. Format yyyy/mm/dd"
					<< endl;
			cin >> date;
			cout
					<< "Please enter in the time of the transaction in question. Format hh:mm:ss"
					<< endl;
			cin >> time;
			cout << "Please enter in the credit card account number." << endl;
			cin >> creditCardNumber;

			if (creditCardNumber.size() != 16
					|| atoi(creditCardNumber.c_str()) == 0) {
				throw ApplicationException(inputError);
			}

			// Select all transactions with a date, time, and account number equal to given values
			string input =
					"QUERY transactionQuery SELECT * FROM Transactions WHERE ((purchaseDate = "
							+ date + ") AND (purchaseTime = " + time
							+ ") AND (accountNumber = " + creditCardNumber
							+ "))";
			error = db.IssueCommand(input);
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("PRINT TABLE transactionQuery");
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("DROP TABLE transactionQuery");
			if (error != 0) {
				throw ApplicationException(error);
			}

			break;
		}

			// Uses two given dates to show all transactions within those dates
		case 11: {
			string startingDate;
			string endingDate;

			cout
					<< "Please enter the starting date of your query. Format yyyy/mm/dd"
					<< endl;
			cin >> startingDate;
			cout
					<< "Please enter the ending date of your query. Format yyyy/mm/dd"
					<< endl;
			cin >> endingDate;

			// Select all transactions with the purchaseDate greater than or equal to one date and less than another
			string input =
					"QUERY dateQuery SELECT * FROM Transactions WHERE ((purchaseDate >= "
							+ startingDate + ") AND (purchaseDate < "
							+ endingDate + "))";
			error = db.IssueCommand(input);
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("PRINT TABLE dateQuery");
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("DROP TABLE dateQuery");
			if (error != 0) {
				throw ApplicationException(error);
			}

			break;
		}

			// Show all transactions between a given range of times
		case 12: {
			string startingTime;
			string endingTime;

			cout
					<< "Please enter the starting time of your query. Format hh:mm:ss (military time)"
					<< endl;
			cin >> startingTime;
			cout
					<< "Please enter the ending time of your query. Format hh:mm:ss (military time)"
					<< endl;
			cin >> endingTime;

			// Select all transactions where the purchaseTime is greater than or equal to one given time and less than another
			string input =
					"QUERY timeQuery SELECT * FROM Transactions WHERE ((purchaseTime >= "
							+ startingTime + ") AND (purchaseTime < "
							+ endingTime + "))";
			error = db.IssueCommand(input);
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("PRINT TABLE timeQuery");
			if (error != 0) {
				throw ApplicationException(error);
			}

			error = db.IssueCommand("DROP TABLE timeQuery");
			if (error != 0) {
				throw ApplicationException(error);
			}

			break;
		}

			//Exit the menu loop
		case 13: {
			cout << "Good bye!" << endl;
			break;
		}

			// Incorrect Menu option, so throw an error
		default: {
			throw ApplicationException(inputError);
			break;
		}
		}
	}

	return 0;
}

// Catches all errors and uses a code to get the correct error message
catch (ApplicationException &e) {
	switch (e.getCode()) {
	case 1:
		cerr << "Invalid Input" << endl;
		break;
	case 2:
		cerr << "Type Conversion Problem" << endl;
		break;
	case 3:
		cerr << "Invalid Table" << endl;
		break;
	case 4:
		cerr << "Invalid Attribute" << endl;
		break;
	case 5:
		cerr << "Duplicate Key" << endl;
		break;
	case 6:
		cerr << "Name Already Exist" << endl;
		break;
	case 7:
		cerr << "You input something wrong." << endl;
		break;
	default:
		cerr << "Unknown Error." << endl;
		break;
	}
	return 1;
}
