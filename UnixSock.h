#ifndef UNIX_SOCK_H
#define UNIX_SOCK_H

#include<sys/socket.h>
#include<fcntl.h>
#include<sys/un.h>
#include<string>
#include<string.h>
#include"Sock.h"

class UnixSock:public Sock
{
public:
	UnixSock();
	UnixSock(int);
	//int Bind(std::string sock_file,int port);
	int Bind(std::string sockfile);
	int Connect(std::string sockfile);
	UnixSock Accept(sockaddr*, socklen_t*);
//private:
//	int sock;
};

#endif
