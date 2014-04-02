/*
 * ServerMethods.h
 *
 *  Created on: Apr 21, 2012
 *      Author: gigemjt
 */

#ifndef SERVERMETHODS_H_
#define SERVERMETHODS_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
using namespace std;
class socket_info
{
public:
	string roomName;
	struct addrinfo hints, *res;
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	char* port_number;
	int sockfd;
	int backlog_size;
	int new_fd;
//	int bind_value;
//	int listen_value;
//	int connection_value;
	//only for the last one sent
	char *sendMsg;
	int sendMsgLength;
	int bytes_sent;
	//only for the last one read
	char *recMsg;
	int recMsgLength;
	int bytes_read;
};
void duplicate(socket_info* si,socket_info* out);
void set_up_address(socket_info* si);
int my_socket(socket_info* si);
void my_bind(socket_info* si);
void my_listen(socket_info* si);
socket_info* my_accept(socket_info* si,socket_info* si2);
void my_connect(socket_info* si);

char* my_recv(socket_info* si,int amount_to_read);
int my_send(socket_info* si,char * msg);

char* my_recv_from(socket_info* si,int amount_to_read);
int my_send_to(socket_info* si,char* msg);

socket_info* open_server(char * port,socket_info si_temp);
socket_info* create_socketfinfo(char * port,socket_info *si);
socket_info* open_client(char * port,socket_info si_temp);
#endif /* SERVERMETHODS_H_ */
