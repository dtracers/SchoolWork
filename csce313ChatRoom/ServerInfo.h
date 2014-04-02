/*
 * ServerInfo.h
 *
 *  Created on: Apr 26, 2012
 *      Author: gigemjt
 */

#ifndef SERVERINFO_H_
#define SERVERINFO_H_
#include <vector>
#include <map>
#include <string>
#include "ServerMethods.h"
using namespace std;
class ServerInfo
{
public:
	vector<string> roomNames;
	map<string,vector<socket_info*>*> rooms;
	socket_info* getInfo(string room);
	void addRoom(string,socket_info*);
	ServerInfo();
	virtual ~ServerInfo();
};

#endif /* SERVERINFO_H_ */
