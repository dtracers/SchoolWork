#include <iostream>
#include <fstream>
#include<sstream>
#include "Database.h"
#include "parser.h"
#include "LogicHandler.h"
#include "ExpressionTree.h"
#include <iostream>
#include <algorithm>
int Dumb_main();
int main() {
/*	cout<<"STARTING TEST"<<endl;
	Dumb_main();
	cout<<"TESTING THERES"<<endl;
	
	 Database d = Database();
	 d.createTable("Hi");
	 d.createTableColumn("Hi", "1", "int");
	 cout<<d.countRecordsByTable("Hi")<<endl;
	 d.createTable("Hi1");
	 d.createTableColumn("Hi1", "1", "varchar(2)");
	 d.deleteTable("Hi1");
	 cout<<d.countAll()<<endl;
	 d.printTable("Hi");
	 d.printTable("Hi1");


	try
	{
		Database* db=new Database();
		db->setDebug(true);
		string command;
		string choice;
		string data;

		command = "CREATE TABLE tab (uin int, PRIMARY KEY uin);";
		db->create(command);

		command = "INSERT INTO tab (uin) VALUES (91900);";
		db->insert(command);
		db->list("tab");
		db->create("PRINT ALL;");
		command ="SELECT * FROM tab WHERE (uin > 0) STORE print;";
		db->query(command);
		db->create("PRINT ALL;");
	}catch(DatabaseException& e )
	{
		cout<<e<<endl;
	}

	
	try
	{
		Database* d=new Database();
		d->create("CREATE TABLE Individual_Transactions (Date date, Time time, Credit_Card_Number int, Vendor_Name varchar(100), Amount_of_Transaction float, Category_of_Purchase varchar(50), Transaction_ID_Number varchar(50));");
		string rows = "(Date, Time, Credit_Card_Number, Vendor_Name, Amount_of_Transaction, Category_of_Purchase, Transaction_ID_Number)";
		d->insert("INSERT INTO Individual_Transactions "+rows);
		d->create("PRINT ALL;");
	}catch(DatabaseException& e )
	{
		cout<<e<<endl;
	}
*/
	try {
		Database* d = new Database();
		//*;
		d->setDebug(true);
		parser p(d);
		//ifstream ifs ( "createTable.txt" , ifstream::in );
		//ifstream ifs ( "SimpleQuery.txt" , ifstream::in );
		ifstream ifs("commands.txt", ifstream::in);
		string total;
		while (!ifs.eof()) {
			string temp;
			ifs >> temp;
			total += temp + " ";
		}
		//	cerr<<total<<"\n";
		//p.parse(total);
		d->query(total);
	} catch (DatabaseException& e) {
		cout << e.getMessage() << endl;
		cout << e << endl;
	}
	/*
	 for(int pos=0;pos<2000;pos++)
	 {
	 for(int index=0;index<24;index++)
	 {
	 int value=((index&31)<<15)+(pos&32767)+(index<<20);
	 int new_index=(((value)>>15)&31);
	 int size=(value)>>20;
	 int new_pos=value&32767;
	 if(new_index!=index||pos!=new_pos||index!=size)
	 {
	 cout<<"HERE"<<endl;
	 }

	 //cout<<"WHAT "<<what<<endl;
	 cout<<"TOTAL VALUE!!! "<<value<<endl;
	 cout<<"TOTAL SIZE!!! "<<value<<endl;
	 cout<<"INDEX: "<<index<<" = "<<new_index<<" POSITION: "<<pos<<" = "<<new_pos<<endl;

	 //	cout<<"NOT! "<<endl;
	 }
	 }
	
	//TODO: now we need to do it so that it will return other types of info
	
	 cout<<"I miss you"<<endl;
	 LogicExpression::LogicHandler l("price+(8*2)+(7*2)");
	 l.parse();
	 LogicExpression::ExpressionTree* tree=l.getTree();
	 tree->toString();
	 cout<<"TIME TO EVALUATE"<<endl;
	 for(int k=0;k<10;k++)
	 {
	 vector<string> variables;
	 variables.push_back("price");
	 stringstream numer;
	 numer<<k;
	 string temp;
	 numer>>temp;
	 vector<string> replacements;
	 replacements.push_back(temp);
	 int vresult=tree->evaluate(variables,replacements);
	 cout<<"result= "<<vresult<<" k= "<<k<<endl;
	 }
	 cout<<"end1?"<<endl;
	 tree->toString();
	 cout<<endl;
	 cout<<"I finished!"<<endl;
	*/ 
}

/*

const int MAX_STR_LEN = 50;

string removeSpaces(string s)
{
	if (s[0] == ' ')
		s.erase(0,1);
	if (s[s.length()-1] == ' ')
		s.erase(s.length()-1, s.length());

	size_t found = s.find(' ');
	if (found != string::npos)
	{
		s.replace(found,1,"_");
		removeSpaces(s);
	}
	else
		return s;
}

void createTables (Database *db)
{
	db->create("CREATE TABLE Transactions "
		"("
			"Date date,"
			"Time time,"
			"Card_Number varchar(16),"
			"Vendor_Name varchar(50),"
			"Amount float,"
			"Category varchar(50),"
			"Vendor_ID varchar(50),"
			"PRIMARY KEY Vendor_ID"
		");"
	);

	db->create("CREATE TABLE Vendors "
		"("
			"Name varchar(50),"
			"Type varchar(50),"
			"Date_of_Authorization date,"
			"ID varchar(50),"
			"PRIMARY KEY ID"
		");"
	);

	db->create("CREATE TABLE Customers "
		"("
			"First_Name varchar(50),"
			"Last_Name varchar(50),"
			"Date_of_Membership date,"
			"Card_Number varchar(16),"
			"Balance float,"
			"PRIMARY KEY Card_Number"
		");"
	);
}

void populateTransactions(Database *db)
{
	cout << "Building transactions table...\n";
	cout << "File name (type NULL to skip): ";
	string fName;
	cin >> fName;

	if (fName == "NULL")
		return;
	cout<<"so far so good"<<endl;
	char inputToken[MAX_STR_LEN];
	string date;
	string time;
	string cardNumber;
	string vendorName;
	string amount;
	string category;
	string vendorID;
	int errorCode;

	ifstream ifs(fName.c_str());
	while (ifs.good())
	{
		cerr<<"looping"<<endl;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		cerr<<"made it past here"<<endl;
		date = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		cerr<<"made it past here2"<<endl;
		time = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		cerr<<"made it past here3"<<endl;
		cardNumber = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		cerr<<"made it past here4"<<endl;
		vendorName = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		cerr<<"made it past here5"<<endl;
		amount = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		cerr<<"made it past here6"<<endl;
		category = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN);
		cerr<<"made it past here7"<<endl;
		vendorID = inputToken;

		date = removeSpaces(date);
		cerr<<"made it past here8"<<endl;
		time = removeSpaces(time);
		cardNumber = removeSpaces(cardNumber);
		cerr<<"made it past here9"<<endl;
		vendorName = removeSpaces(vendorName);
		cerr<<"made it past here9.5"<<endl;
		amount = removeSpaces(amount);
		cerr<<"made it past here10"<<endl;
		category = removeSpaces(category);
		vendorID = removeSpaces(vendorID);
		cerr<<"so far so good2"<<endl;
		cerr<<amount<<endl;
		string command="INSERT INTO Transactions (Date,Time,Card_Number,Vendor_Name,Amount,Category,Vendor_ID)VALUES([" + date + "],[" + time + "]," + cardNumber + vendorName +  amount + category +  vendorID + ");";
		errorCode = db->insert(command

		);


		if (errorCode != 0)
		{
			//deal with errors
		}

	}
	cerr<<"I finished trans.txt"<<endl;
}

void populateVendors(Database *db)
{
	cout << "Building vendors table...\n";
	cout << "File name (type NULL to skip): ";
	string fName;
	cin >> fName;

	if (fName == "NULL")
		return;

	char inputToken[MAX_STR_LEN];
	string name;
	string type;
	string date;
	string id;
	int errorCode;

	ifstream ifs(fName.c_str());
	while (ifs.good())
	{
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		name = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		type = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		date = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN);
		id = inputToken;

		name = removeSpaces(name);
		type = removeSpaces(type);
		date = removeSpaces(date);
		id = removeSpaces(id);
		errorCode = db->insert(
			"INSERT INTO Vendors "
			"("
				"Name,"
				"Type,"
				"Date_of_Authorization,"
				"ID"
			")"
			"VALUES"
			"("
				"" + name + ","
				"" + type + ","
				"[" + date + "],"
				"" + id + ""
			");"
		);

		if (errorCode != 0)
		{
			//deal with errors
		}
	}
}

void populateCustomers(Database *db)
{
	cout << "Building customers table...\n";
	cout << "File name (type NULL to skip): ";
	string fName;
	cin >> fName;

	if (fName == "NULL")
		return;

	char inputToken[MAX_STR_LEN];
	string firstName;
	string lastName;
	string date;
	string cardNumber;
	string balance;
	int errorCode;

	ifstream ifs(fName.c_str());
	while (ifs.good())
	{
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		firstName = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		lastName = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		date = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN, ',');
		cardNumber = inputToken;
		ifs.getline(inputToken, MAX_STR_LEN);
		balance = inputToken;

		firstName = removeSpaces(firstName);
		lastName = removeSpaces(lastName);
		date = removeSpaces(date);
		cardNumber = removeSpaces(cardNumber);
		balance = removeSpaces(balance);

		errorCode = db->insert(
			"INSERT INTO Customers "
			"("
				"First_Name,"
				"Last_Name,"
				"Date_of_Membership,"
				"Card_Number,"
				"Balance"
			")"
			"VALUES"
			"("
				"" + firstName + ","
				"" + lastName + ","
				"[" + date + "],"
				"" + cardNumber + ","
				"" + balance + ""
			");"
		);

		if (errorCode != 0)
		{
			//deal with errors
		}
	}
}

void monthlyStatement(Database *db)
{
	cout << "Credit card number: ";
	string cardNumber;
	cin >> cardNumber;

	cout << "Month (01-12): ";
	string month;
	cin >> month;

	cout << "Year (YYYY-2012): ";
	string year;
	cin >> year;

	string date1 = "[" + year + "/" + month + "/01]";

	int m = atoi(month.c_str());
	if (m == 12)
		month = "01";
	else
	{
		m++;
		if (m >= 10)
			month = m;
		else
			month = "0" + m;
	}
	string date2 = "[" + year + "/" + month + "/01]";

	db->query(
		"SELECT * "
		"FROM Transactions "
		"WHERE ((Card_Number = " + cardNumber + ") && (Date >= " + date1 + ") && (Date < " + date2 + ")) "
		"STORE Monthly_Transactions;"
	);
}

void simpleTransactionQuery(Database *db, string column, string target)
{
	db->query(
		"SELECT * "
		"FROM Transactions "
		"WHERE (" + column + " = " + target + ") "
		"STORE transactionQuery;"
	);
}

void rangedTransactionQuery(Database *db, string column, string startTarget, string endTarget)
{
	db->query(
		"SELECT * "
		"FROM Transactions "
		"WHERE (" + column + " >= " + startTarget + ") && (" + column + " <= " + endTarget + ") "
		"STORE transactionQuery;"
	);
}

void vendorSummary(Database *db)
{
	cout << "Vendor ID: ";
	string id;
	cin >> id;

	simpleTransactionQuery(db, "Vendor_ID", id);
}

void singularTransactionSearch(Database *db)
{
	cout << "Type 'H' for a list of commands and 'Q' to go back to the previous menu.\n\n";
	char command;
	while (294)
	{
		cin >> command;
		switch (command)
		{
			case 'D':
			{
				cout << "Date (YYYY/MM/DD): ";
				string date;
				cin >> date;
				date = "[" + date + "]";
				simpleTransactionQuery(db, "Date", date);
				break;
			}
			case 'T':
			{
				cout << "Time (HH:MM:SS): ";
				string time;
				cin >> time;
				time = "[" + time + "]";
				simpleTransactionQuery(db, "Time", time);
				break;
			}
			case 'N':
			{
				cout << "Card Number: ";
				string cardNumber;
				cin >> cardNumber;
				simpleTransactionQuery(db, "Card_Number", cardNumber);
				break;
			}
			case 'V':
			{
				cout << "Vendor Name: ";
				string name;
				cin >> name;
				simpleTransactionQuery(db, "Vendor_Name", name);
				break;
			}
			case 'A':
			{
				cout << "Amount: ";
				string amt;
				cin >> amt;
				simpleTransactionQuery(db, "Amount", amt);
				break;
			}
			case 'C':
			{
				cout << "Category: ";
				string category;
				cin >> category;
				simpleTransactionQuery(db, "Category", category);
				break;
			}
			case 'I':
			{
				cout << "Vendor ID: ";
				string id;
				cin >> id;
				simpleTransactionQuery(db, "Vendor_ID", id);
				break;
			}
			case 'H':
				cout << "Commands:\n"
					 << "D - Date\n"
					 << "T - Time\n"
					 << "N - Card Number\n"
					 << "V - Vendor Name\n"
					 << "A - Amount\n"
					 << "C - Category\n"
					 << "I - Vendor ID\n"
					 << "H - Help\n"
					 << "Q - Back tp previous menu\n\n";
				break;
			case 'Q':
				return;
			default:
				cerr << "Invalid command. Type 'H' for assistance.\n";
				break;
		}
	}
}

void rangedTransactionSearch(Database *db)
{
	cout << "Type 'H' for a list of commands and 'Q' to go back to the previous menu.\n\n";
	char command;
	while (294)
	{
		cin >> command;
		switch (command)
		{
			case 'D':
			{
				cout << "Start Date (YYYY/MM/DD): ";
				string date1;
				cin >> date1;
				date1 = "[" + date1 + "]";

				cout << "End Date (YYYY/MM/DD): ";
				string date2;
				cin >> date2;
				date2 = "[" + date2 + "]";

				rangedTransactionQuery(db, "Date", date1, date2);
				break;
			}
			case 'T':
			{
				cout << "Start Time (HH:MM:SS): ";
				string time1;
				cin >> time1;
				time1 = "[" + time1 + "]";

				cout << "End Time (HH:MM:SS): ";
				string time2;
				cin >> time2;
				time2 = "[" + time2 + "]";

				rangedTransactionQuery(db, "Time", time1, time2);
				break;
			}
			case 'A':
			{
				cout << "Low Amount: ";
				string amount1;
				cin >> amount1;

				cout << "High Amount: ";
				string amount2;
				cin >> amount2;

				rangedTransactionQuery(db, "Amount", amount1, amount2);
				break;
			}
			case 'H':
				cout << "Commands:\n"
					 << "D - Date Range\n"
					 << "T - Time Range\n"
					 << "A - Amount Range\n"
					 << "H - Help\n"
					 << "Q - Back tp previous menu\n\n";
				break;
			case 'Q':
				return;
			default:
				cerr << "Invalid command. Type 'H' for assistance.\n";
				break;
		}
	}
}

int Dumb_main()
{
	int result;
	string queryString;
	string queryResult;
	Database *db=new Database();
	//Creating Tables
	result = db->create("CREATE TABLE Artist (ArtistID int, Name varchar(50), FamousDate Date, FamousTime Time, Age int);");
	if(result != 0) {
		cout <<" Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->create("CREATE TABLE Song (SongID int, Name varchar(75), Float Price, ArtistID int, ReleaseDate Date);");
	if(result != 0) {
		cout << "Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->create("CREATE TABLE TopHits (SongID int, ArtistID int, Rating int);");
	if(result != 0) {
		cout <<" Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->create("CREATE TABLE TempTable (Blah int, Blee float, Bloo Date);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->create("CREATE TABLE CompareTable (SongID int);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	//
	//Inserting into the tables
	cout << "Arist Table Row Count: " << db->recordCount("Artist") << endl;
	result = db->insert("INSERT INTO Artist (ArtistID, Name, FamousDate, FamousTime, Age) VALUES (10, Britney Spears, [1990/01/10], [23:45:10], 26);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Artist (ArtistID, Name, FamousDate, FamousTime, Age) VALUES (15, Rihanna, [2001/10/09], [12:46:38], 30);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Artist (ArtistID, Name, FamousDate, FamousTime, Age) VALUES (12, Enrique Englias, [2011/05/12], [14:20:10], 27);");
	if(result != 0) {
		cout <<"  Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Artist (ArtistID, Name, FamousDate, FamousTime, Age) VALUES (4, Taylor Swift, [2005/12/25], [09:09:09], 22);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	cout << "Arist Table Row Count: " << db->recordCount("Artist") << endl;
	//
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (100, Till The World Ends, 0.99, 10, [2005/03/15]);");
	if(result != 0) {
		cout <<"  Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (101, Criminal, 0.95, 10, [2005/07/15]);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (102, Baby, 1.99, 10, [1995/07/20]);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (103, Circus, 2.99, 10, [2005/03/15]);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	//
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (200, Wrong Song, 0.99, 15, [2005/03/15]);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (201, Distrubia, 0.95, 15, [2005/07/15]);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (202, Love The Way You Lie, 1.99, 15, [1995/07/20]);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (203, Only Girl, 2.99, 15, [2005/03/15]);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	//
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (300, Tonight, 0.99, 12, [2005/03/15]);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (301, I Like It, 0.95, 12, [2005/07/15]);");
	if(result != 0) {
		cout << " Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (302, Hero, 1.99, 12, [1995/07/20]);");
	if(result != 0) {
		cout <<"  Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (303, Dirty Dancer, 2.99, 12, [2005/03/15]);");
	if(result != 0) {
		cout <<"  Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	//
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (400, Love Story, 0.99, 4, [2005/03/15]);");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (401, You Belong With Me, 0.95, 4, [2005/07/15]);");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (402, Mine, 1.99, 4, [1995/07/20]);");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO Song (SongID, Name, Price, ArtistID, ReleaseDate) VALUES (403, The Story Of US, 2.99, 4, [2005/03/15]);");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	//
	result = db->insert("INSERT INTO TopHits (SongID, ArtistID, Rating) VALUES (100, 10);");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO TopHits (SongID, ArtistID, Rating) VALUES (300, 12);");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	//
	result = db->insert("INSERT INTO TempTable (Blah, Blee, Bloo) VALUES (10, 10.10, [2010/10/10]);");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	//
	result = db->insert("INSERT INTO CompareTable (SongID) VALUES (303);");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	result = db->insert("INSERT INTO CompareTable (SongID) VALUES (103);");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	//
	//Updating a song name
	cout << db->list("Song") << endl;
	result = db->update("UPDATE TABLE Song SET (Name) VALUES (We Found Love) WHERE SongID = 200;");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}
	cout << db->list("Song") << endl;
	result = db->update("UPDATE TABLE Artist SET (FamousTime) VALUES ([10:30:30]) WHERE ArtistID = 10;");
	if(result != 0) {
		cout << Error: " << result << " Message: " << db->getErrorMessage() << endl;
	}

	//
	//Delete a row
	cout << db->list("TempTable") << endl;
	db->deleteRows("DELETE FROM TempTable WHERE Blah = 10");
	cout << db->list("TempTable") << endl;
	//
	//Delete a table
	cout << "TempTable Record Count: " << db->recordCount("TempTable") << endl;
	db->drop("TempTable");
	cout << "Returns error meaning TempTable doesn't exist: " << db->recordCount("TempTable") << endl;
	//
	//Queries!!!!
	queryString = "SELECT Sum("Price") AS TotalPrice, Min("ReleaseDate") As FirstRelease, Max("ReleaseDate") AS LastRelease, Count("SongID") AS TotalSongs FROM Songs WHERE SongID >= 100 STORE QueryResult;";
	try {
		cout << "Query Operations Result:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	queryString = "SELECT * FROM Songs WHERE Price >= 1.00 STORE QueryResultTwo;";
	try {
		cout << "SELECT * Result:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	queryString = "SELECT Artist.Name FROM Artist, TopHits WHERE Arist.ArtistID = TopHits.ArtistID STORE QueryResultThree;";
	try {
		cout << "Multitable, Artists with Top Hits:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	queryString = "SELECT Name FROM Song WHERE Price > 1.00 AND Price < 2.00 STORE QueryResultFour;";
	try {
		cout << "AND Operator:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	queryString = "SELECT Name FROM Song WHERE Price > 1.00 OR Price < 2.00 STORE QueryResultFive;";
	try {
		cout << "OR Operator:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	queryString = "SELECT Name FROM Song WHERE NOT (Price < 2.00 STORE) QueryResultSix;";
	try {
		cout << "NOT Operator:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	queryString = "SELECT Name FROM Song WHERE SongID >=ANY CompareTable STORE QueryResultSeven;";
	try {
		cout << "ANY:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	queryString = "SELECT Name FROM Song WHERE SongID >=ALL CompareTable STORE QueryResultEight;";
	try {
		cout << "ALL:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	queryString = "SELECT Name FROM Song WHERE SongID IN CompareTable STORE QueryResultNine;";
	try {
		cout << "IN:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	queryString = "SELECT Name FROM Song WHERE EXISTS CompareTable STORE QueryResultTen;";
	try {
		cout << "EXISTS:" << endl << db.query(queryString) << endl;
	}
	catch(DatabaseException& e) {
		cout << "Query Error: " << e.getErrorMessage() << " on the following query:" << endl << queryString << endl;
	}
	*/
//}
