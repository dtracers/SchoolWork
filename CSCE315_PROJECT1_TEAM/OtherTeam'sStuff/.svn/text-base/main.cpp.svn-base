#include "Database.h"
#include <iostream>

using namespace std;

int main() {
   Database db;

   if(db.IssueCommand("CREATE TABLE TestTable (Name varchar(10), Money int, Times time, Dates date)") == SUCCESS) {
      cout<<"CREATED!"<<endl;
   }

   if(db.IssueCommand("INSERT INTO TestTable VALUES (Bob, 1000, 23:12:11, 2012/12/21)") == SUCCESS) {
      cout<<"ADDED TUPLE!"<<endl;
   }

   if(db.IssueCommand("INSERT INTO TestTable VALUES (Frank, 0, 23:13:11, 2012/12/21)") == SUCCESS) {
      cout<<"ADDED TUPLE!"<<endl;
   }

   if(db.IssueCommand("INSERT INTO TestTable VALUES (Jim, 10000, 23:12:11, 2012/12/21)") == SUCCESS) {
      cout<<"ADDED TUPLE!"<<endl;
   }
   
   if(db.IssueCommand("PRINT TABLE TestTable") == SUCCESS) {
      cout<<"PRINTED!"<<endl;
   }

   if(db.IssueCommand("DROP TABLE TestTable") == SUCCESS) {
      cout<<"DELETED?"<<endl;
   }

   if(db.IssueCommand("PRINT TABLE TestTable") == SUCCESS) {
      cout<<"NOPE :-("<<endl;
   } else {
      cout << "DELETED, YAY!"<<endl;
   }

   char exit;
   cout<<"Enter any char to exit: ";
   cin>>exit;

   return 0;
}