/*
 * ServerMethods.c
 *
 *  Created on: Apr 21, 2012
 *      Author: gigemjt
 */


#ifndef __ServerMethods_C_
#define __ServerMethods_C_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ServerMethods.h"
using namespace std;
socket_info* open_server(char * port,socket_info si_temp)
{
	printf("Opening server on port %s\n",port);
	socket_info *si=create_socketfinfo(port,&si_temp);

	set_up_address(si);
	printf("Address created on port %s\n",si->port_number);

	my_socket(si);
	my_bind(si);
	my_listen(si);
	return si;
}

socket_info* open_client(char * port,socket_info si_temp)
{
	printf("Opening client on port %s\n",port);
	socket_info *si=create_socketfinfo(port,&si_temp);

	set_up_address(si);
	printf("Address created on port %s\n",si->port_number);

	my_socket(si);
	my_connect(si);
//	my_bind(si);
//	my_listen(si);
	return si;
}


void duplicate(socket_info* si,socket_info* out)
{
	out->hints=si->hints;
	out->res=si->res;
	out->their_addr=si->their_addr;
	out->addr_size=si->addr_size;
	out->port_number=si->port_number;
	out->sockfd=si->sockfd;
	out->backlog_size=si->backlog_size;
}

socket_info* create_socketfinfo(char * port,socket_info *si)
{
	si->port_number=port;
	return si;
}

void set_up_address(socket_info* si)
{
	struct addrinfo hints, *res;
	memset(&(hints), 0, sizeof (hints));

	hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	getaddrinfo(0, si->port_number, (&hints), &res);
	si->hints=hints;
	si->res=res;
}


int my_socket(socket_info* si)
{
	int sockfd = socket(si->res->ai_family, si->res->ai_socktype, si->res->ai_protocol);
	si->sockfd=sockfd;
	if(sockfd>=0)
		printf("socket created feed=%d\n",sockfd);
	else
	{
		cerr<<"Socket unssecsfull"<<endl;
	}
	return sockfd;
}


void my_bind(socket_info* si)
{
	int bindValue=bind(si->sockfd, si->res->ai_addr, si->res->ai_addrlen);
//	si->bind_value=bindValue;
	if(bindValue>=0)
	printf("binding was successful %d\n",bindValue);
	else
	{
		close(si->sockfd);
		printf("binding was not successful");
	}
}
void my_listen(socket_info* si)
{
	int listenValue = listen(si->sockfd,si->backlog_size);
//	si->listen_value=listenValue;
	if(listenValue>=0)
	printf("listening %d\n",listenValue);
	else
		printf("listening was not successful");
}
socket_info* my_accept(socket_info* si,socket_info* si2)
{
	si->addr_size= sizeof si->their_addr;
	duplicate(si,si2);
	int new_fd = accept(si->sockfd, (struct sockaddr *)&(si->their_addr), &(si->addr_size));
	si->new_fd=new_fd;
	si2->sockfd=new_fd;
	printf("accepted new feed is %d\n",new_fd);
	return si2;
}
char* my_recv(socket_info* si,int amount_to_read)
{
	char* buf;
	buf=(char*)malloc(amount_to_read * sizeof(char));
	int bytesRead=recv(si->sockfd,buf,amount_to_read,0);
	si->recMsg=buf;
	si->sendMsgLength=amount_to_read;
	si->bytes_read=bytesRead;
	//printf("bytesRead is %d",bytesRead);
	if(bytesRead==0)
	{
		return 0;
	}else if(bytesRead>0)
		return buf;
	else
	{
		return NULL;
	//	printf("ERROR while recieving message");
	}
}
int my_send(socket_info* si,char * msg)
{
	si->sendMsg=msg;
	si->sendMsgLength=strlen(msg);
	si->bytes_sent=send(si->sockfd,msg,si->sendMsgLength,0);
	return si->bytes_sent;
}
char* my_recv_from(socket_info* si,int amount_to_read)
{
	char* buf;
	buf=(char*)malloc(amount_to_read * sizeof(char));
	sockaddr* sock=(sockaddr*)(&(si->their_addr));
	int bytesRead=recvfrom(si->sockfd,(void*)buf,(unsigned long int )amount_to_read,0,sock,&(si->addr_size));
	si->recMsg=buf;
	si->sendMsgLength=amount_to_read;
	si->bytes_read=bytesRead;
	printf("bytesRead is %d",bytesRead);
	if(bytesRead==0)
	{
		return 0;
	}else if(bytesRead>0)
		return buf;
	else
	{
		printf("ERROR while recieving message");
	}
	return buf;
}
int my_send_to(socket_info* si,char* msg)
{
	si->sendMsg=msg;
	si->sendMsgLength=strlen(msg);
	sockaddr* sock=(sockaddr*)(&(si->their_addr));
	si->bytes_sent=sendto(si->sockfd,msg,si->sendMsgLength,0,sock,si->addr_size);
	return si->bytes_sent;
}
void my_connect(socket_info* si)
{
	int connection=connect(si->sockfd, si->res->ai_addr, si->res->ai_addrlen);
	if(connection>=0)
		printf("Connected Successfully! %d\n",connection);
	else
	{
		printf("Connected badly!!");
	}
}
#endif
