/*
 * client.c
 *
 *  Created on: Apr 21, 2012
 *      Author: gigemjt
 */
#include <stdio.h>
#include "ServerMethods.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
char* mainPort="3490";
char* command(string in,socket_info* si);
int state;
int stateoption;
volatile bool stillInRoom=true;
void recieveMessages(socket_info* si);
int main()
{
	state=0;
	printf("running client!");
	socket_info si_temp;
	socket_info *si=open_client(mainPort,si_temp);
	printf("Client connected\n");
	string input="";
	cout<<"INSTERT COMMAND"<<endl;
	cout<<"CREATE = create a room"<<endl;
	cout<<"JOIN = join an already existing room"<<endl;
	cout<<"DELETE = delete an already existing room"<<endl;
	cin>>input;
	if(input=="CREATE")
	{
		cout<<"Table name";
		string tablenm;
		string mesg="c ";
	//	cerr<<"creation message: "<<mesg<<endl;
		my_send(si,(char*)mesg.c_str());
		cin>>tablenm;
		my_send(si,(char*)tablenm.c_str());
		cout<<"Table Name sent"<<endl;
	//	cout<<"getting port on feed "<<si->sockfd<<endl;
		char * port=my_recv(si,4);
	//	cerr<<"recieved port!"<<port<<endl;
		socket_info si2_temp;
		socket_info *si2;
		si2=open_client(port,si2_temp);

		my_send(si2,"Connected to room");
		string input;

		pthread_t thread;
		pthread_create(&thread,NULL,(void* (*)(void*))recieveMessages,(void*)si2);
		cout<<"Type your message"<<endl;
		cin>>input;
//		cerr<<"Client send info message "<<si2->sockfd<<endl;
		while(input!="quit")
		{
			int bytes_sent=my_send(si2,(char*)input.c_str());
//			cerr<<"bytes sending "<<bytes_sent<<endl;
			cout<<"Type your message"<<endl;
			cin>>input;
		}
		if(input=="quit")
			int bytes_sent=my_send(si2,(char*)input.c_str());
		stillInRoom=false;
		cerr<<"Leaving room"<<endl;
		pthread_exit(NULL);
		close(si2->sockfd);
	}
	if(input=="JOIN")
	{
		my_send(si,"j");
		cout<<"enter TableName"<<endl;
		string input;
		cin>>input;
		my_send(si,(char*)input.c_str());
		cout<<"Table name has been sent"<<endl;
		char * port=my_recv(si,4);
		if(port=="N/A")
		{
			cout<<"Table doesn't exist"<<endl;
		}else
		{
	//		cerr<<"recieved port!"<<port<<endl;
			socket_info si2_temp;
			socket_info *si2;
			si2=open_client(port,si2_temp);
			my_send(si2,"Connected to room");
			pthread_t thread;
			pthread_create(&thread,NULL,(void* (*)(void*))recieveMessages,(void*)si2);
			cout<<"Type your message"<<endl;
			cin>>input;
//			cerr<<"Client send info message "<<si2->sockfd<<endl;
			while(input!="quit")
			{
				int bytes_sent=my_send(si2,(char*)input.c_str());
//				cerr<<"bytes sending "<<bytes_sent<<endl;
				cout<<"Type your message"<<endl;
				cin>>input;
			}
			if(input=="quit")
				int bytes_sent=my_send(si2,(char*)input.c_str());
			stillInRoom=false;
			cerr<<"Leaving room"<<endl;
			pthread_exit(NULL);
			close(si2->sockfd);
		}
		//needs to sent join table
		//join table
	}
	if(input=="DELETE")
	{
		my_send(si,"d");
		cout<<"enter TableName"<<endl;
		cin>>input;
		my_send(si,(char*)input.c_str());
		char * port=my_recv(si,6);
		if(port=="N/A")
		{
			cout<<"Table doesn't exist"<<endl;
		}
		cerr<<"Table "<<port<<"Deleted"<<endl;
		//delete table
	}
	printf("%d bytes sent ",(si,command(input,si)));

	printf("sending message\n");
	/*
	while(1)
	{
		sleep(30);
		printf("sleeping\n");
	}
	*/
}

char* command(string in,socket_info* si)
{
	bool invalid=true;
	while(invalid)
	{
		if(state==0)
		{
			cerr<<"my state is "<<state<<endl;
			cerr<<"my input is "<<in<<endl;
			string compare="CREATE";
			if(in==compare)
			{
				cout<<"it whent here right?"<<endl;
				state=1;
				stateoption=0;
				return "c";
			}
			invalid=false;
		}else if(state==1)//it means creating deleteing or joining
		{
			char * msg=my_recv(si,20);
			printf("%s\n",msg);
			if(stateoption==0)
			{
				cin>>in;
				cout<<"My Input was "<<in;
				invalid=false;
				return (char*)in.c_str();
			}
		}else if(state==3)//this one means it is constantly writing and reading from chat room
		{
			char * msg=my_recv(si,20);
			printf("%s\n",msg);
			cin>>in;
			invalid=false;
		}
		if(invalid)
		{
			cout<<"Enter a valid command"<<endl;
			string hih;
			cin>>hih;
		}
	}
}

void recieveMessages(socket_info* si)
{
//	cout<<"Prepared to receive messages"<<endl;
//	cout<<"Client recieve message socket info "<<si->sockfd<<endl;
	while(1&&stillInRoom)
	{
		//cerr<<"waiting to get msg"<<endl;
		char* msg=my_recv(si,100);
		if(si->bytes_read>0)
		{
			string s=msg;
			s=s.substr(0,si->bytes_read);
			cout<<"Message Recieved: "<<s<<endl;
		}if(si->bytes_read==0)
		{
			cout<<"it appears server has left"<<endl;
			close(si->sockfd);
			stillInRoom=false;
			break;
		}
		sleep(1);
	}
	pthread_exit(NULL);
}
