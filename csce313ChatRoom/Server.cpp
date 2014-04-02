/*
 * Server.c
 *
 *  Created on: Apr 21, 2012
 *      Author: gigemjt
 */
using namespace std;

#include <stdio.h>
#include "ServerMethods.h"
#include <pthread.h>
#include <time.h>
#include"ServerInfo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
char* mainPort="3490";
ServerInfo* f;
vector<pthread_t> threads;

void ThreadedAcceptConnect(socket_info *si);
void ThreadedAccept(socket_info* si);
void handle_request(socket_info * work);
void handle_slave(socket_info * arg);
string create_room(string name);
void addClientToRoom(socket_info* info,string name);
socket_info* getClientFromRoom(string name);
int delete_room(string room);
socket_info* getClientFromRoom(string name);


int main()
{
	f=new ServerInfo();
	printf("running server wait for client\n");
	socket_info si_temp;
	socket_info *si=open_server(mainPort,si_temp);
	printf("everything is working");
	int k;
	for(k=0;k<1;k++)
	{
		//only go once
		printf("waiting to accept\n");
		socket_info* si2=new socket_info();
		si2=my_accept(si,si2);
		if(si2->sockfd>-1)
		{
			printf("Client Connected\n");
			pthread_t thread;
			pthread_create(&thread,NULL,(void* (*)(void*))ThreadedAcceptConnect,((void*)si));
			handle_request(si2);
			threads.push_back(thread);
		//	si=si2;
		}else
		{
			printf("SOCK FEED IS LESS THAN 0");
		}
		cerr<<"waiting for another client to try and connect"<<endl;
	}
	for(int k=0;k<threads.size();k++)
	{
		int *exitcodep=0;
		int error;
		if (error = pthread_join(threads[k],((void**)&exitcodep)))
		{
			fprintf(stderr, "I Failed to join thread: %s\n",strerror(error));
		}
	}
	pthread_exit(NULL);
	close(si->sockfd);
	/*
	for(int k=0;k<60;k++)
	{
		sleep(60);
	}
	*/
}

void handle_request(socket_info * arg) {
	socket_info *si= arg;
//	printf("debug print\n");
	char* msg;
//	printf("waiting for command\n");
	cerr<<"waiting for command"<<endl;
	msg=my_recv(si,10);
	char command=msg[0];
	cerr<<"I went past my command"<<endl;
	printf("%s message recieved\n",msg);
//	char command;
	//parse command here
	printf("%s message recieved\n",msg);
	switch (command) {
	case 'c':
	{
		printf("YAY!!!");
		msg=my_recv(si,10);//get Name

		printf("%s message recieved\n",msg);
		string n=msg;
		cerr<<"table name "<<n<<endl;
		n=n.substr(0,si->bytes_read);//name is now correct

		//created room here
		string port2=create_room(n);
		cerr<<"server new port is "<<port2<<endl;

		string name=msg;
		socket_info si_temp;
		socket_info *si2;
		char* port=(char*)port2.c_str();

		si2=open_server(port,si_temp);//create server

		my_send(si,port);//send port number
		cout<<"sending port number on feed "<<si->sockfd<<endl;
		addClientToRoom(si2,n);
		cerr<<"port has been sent"<<endl;
		pthread_t thread;


			cerr<<"Waiting to accept"<<endl;
			socket_info* si3=new socket_info();
			si3=my_accept(si2,si3);
			addClientToRoom(si3,n);//this will add each client
	//		add the client to the room;
			msg=my_recv(si3,20);
			cerr<<"HEY CLIENT IS CONNECTED["<<msg<<"]"<<endl;
			pthread_create(&thread,NULL,(void* (*)(void*))ThreadedAccept,(void*)si2);
			handle_slave(si3);


		int* i=0;
		pthread_join(thread,(void**)&i);
	}break;
	case 'j'://join
	{
		cerr<<"Command is join!!!"<<endl;
		char *msg2=my_recv(si,10);//get table name
		string name=msg2;
		name=name.substr(0,si->bytes_read);
		cerr<<"The number of bytes that were read were "<<si->bytes_read<<endl;
		cerr<<"The table name that has been recieved was "<<name<<endl;
		socket_info* si2=getClientFromRoom(name);
		printf("Joining\n");
		if(si2==NULL)
		{
			cerr<<"no table with that name"<<endl;
			my_send(si,"N/A");
		}else
		{
			cerr<<"table exist"<<endl;
			my_send(si,si2->port_number);
		}

		//it should do nothing now because it should be done
	}break;
	//	send(port_num);
	case 'd':
		printf("Deleting");
		msg=my_recv(si,10);//get table name
		string name=msg;
		name=name.substr(0,si->bytes_read);
		delete_room(name);
		my_send(si,(char*)name.c_str());
	//	delete a room;
	}
	pthread_exit(NULL);
}

void handle_slave(socket_info * arg) {
//	cout<<"I am in handle slave"<<endl;
	socket_info *si=arg;
	char* message;
	si->bytes_read=1;
//	cerr<<"the slave socket info is "<<si->sockfd<<endl;
	bool stop=false;
	while (si->bytes_read!=0&&!stop) {
		message=my_recv(si,256);
		if(si->bytes_read>0)
		{
			string s=message;
			s=s.substr(0,si->bytes_read);
			string name=si->roomName;

			if(s=="quit")
			{
				cerr<<"The person has quited\n";
				s="Someone has left the room";
				stop=true;
			}else
			{
				cerr<<"Server recieved message "<<message<<endl;
				cerr<<"sending to all other peoples"<<endl;

			}
			vector<socket_info*> *vector2=f->rooms[name];
			if(vector2!=NULL)
			{
				vector<socket_info*> vect=*vector2;
				for(int k=0;k<vect.size();k++)
				{
					socket_info* info=vect[k];
					int bytessent=my_send_to(info,(char*)s.c_str());
				}
			}else
			{
				stop=true;
				my_send_to(si,"It appears the room has been deleted");
			}
			if(stop)
			{
				break;
			}
			//send to all other people
		}else if(si->bytes_read==0)
		{
			cerr<<"It appears that the client has left"<<endl;
			break;
			//the person no longer exist
		}else if(si->bytes_read<0)
		{
			cerr<<"error with the client"<<endl;
			//why??
		}
		if(!stop)
			sleep(1);
	//	broadcast to all members in the same
	//	chat room;
	}
	cerr<<"i am done reciving messages!!!"<<endl;
//	my_close();
	/* If recv() returns 0, it means the client
		closes the connection */
//	delete current client from this room;
}

void addClientToRoom(socket_info* info,string name)
{
	if(f->rooms[name]==NULL)
	{
		//room doesnt exist;
		cerr<<"failing to add client to room.\n room does not exist: ["<<name<<"]"<<endl;
	}else
	{
		cerr<<f->rooms[name]<<endl;
		f->rooms[name]->push_back(info);
		info->roomName=name;
		cout<<"adding client to room ["<<name<<"] was successful"<<endl;
	}
}

socket_info* getClientFromRoom(string name)
{
	if(f->rooms[name]==NULL)
	{
		//room doesnt exist;
		cerr<<"failing to add client to room.\n room does not exist: ["<<name<<"]"<<endl;
		return NULL;
	}else
	{
		return (*(f->rooms[name]))[0];
	}
}

string create_room(string name)
{
	cerr<<"NAME OF ROOM IS ["<<name<<"]"<<endl;
	int portNumber=0;
	if(f->roomNames.size()>=10)
	{
		//crash
	}
	else
	{
		if(f->rooms[name]==NULL)
		{
			f->roomNames.push_back(name);
			vector<socket_info*>* vect=new vector<socket_info*>();
			f->rooms[name]=vect;
		}else
		{
			//it exist crash
		}
		portNumber=3000+10*f->roomNames.size();
	}
	stringstream m;
	m<<portNumber;
	string out;
	m>>out;
	return out;
}


int delete_room(string room)
{
	if(f->rooms[room]==NULL)
	{
		cerr<<"table doesnt exist"<<endl;
		return -1;
	}else
	{
		f->rooms[room]=NULL;
		cout<<"Table has been deleted"<<endl;
	}
}

void ThreadedAccept(socket_info* si)
{
	int *exitcodep=0;
	socket_info* si3=new socket_info();
	si3=my_accept(si,si3);
	char* msg=my_recv(si3,20);
	cerr<<"HEY CLIENT IS CONNECTED["<<msg<<"]"<<endl;
	pthread_t thread;
	addClientToRoom(si3,si->roomName);
	pthread_create(&thread,NULL,(void* (*)(void*))ThreadedAccept,(void*)si);
	handle_slave(si3);
	int error;
	if (error = pthread_join(thread,((void**)&exitcodep)))
			fprintf(stderr, "I Failed to join thread: %s\n",strerror(error));
}
void ThreadedAcceptConnect(socket_info *si)
{
	printf("waiting to accept\n");
	socket_info* si2=new socket_info();
	si2=my_accept(si,si2);
	if(si2->sockfd>-1)
	{
		printf("Client Connected\n");
		pthread_t thread;
		pthread_create(&thread,NULL,(void* (*)(void*))ThreadedAcceptConnect,((void*)si));
		threads.push_back(thread);
		handle_request(si2);
	}else
	{
		ThreadedAcceptConnect(si);
	}
	pthread_exit(NULL);
}
