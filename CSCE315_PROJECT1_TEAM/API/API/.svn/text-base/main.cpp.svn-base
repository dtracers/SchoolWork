#include <iostream>
#include <fstream>
#include "Database.h"
#include "parser.h"
#include "LogicHandler.h"
#include "ExpressionTree.h"
int main()
{
	/*
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
	*/

	//*
	try
	{
		Database* d=new Database();
		parser p(d);
		//ifstream ifs ( "createTable.txt" , ifstream::in );
		ifstream ifs ( "SimpleQuery.txt" , ifstream::in );
		string total;
		while(!ifs.eof())
		{
			string temp;
			ifs>>temp;
			total+=temp+" ";
		}
	//	cerr<<total<<"\n";
		p.parse(total);
	}catch(DatabaseException& e)
	{
		cout<<e<<endl;
	}
//	*/

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
//	*/
    /*
	cout<<"I miss you"<<endl;
	LogicExpression::LogicHandler l("priceAND(8*2)+(7*2)");
	l.parse();
	cout<<"end1?"<<endl;
	l.getTree()->toString();
	cout<<"I finished!"<<endl;
//	*/
}
