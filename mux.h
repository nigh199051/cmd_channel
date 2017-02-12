#ifndef MUX_H
#define MUX_H

#include"event_mgr.h"
#include"conn_status.h"
#include"Sock.h"
#include"UnixSock.h"
#include<string>
//#include<sys/socket.h>
//#include<arpa/inet.h>
//#include<fcntl.h>
#include<iostream>
#include<map>
#include<signal.h>


class mux
{
public:
	mux(std::string ip,int port);
	void do_it();
	void sock_init();
	//void hello();
	conn_status* cs;
	event_mgr* emgr;
	UnixSock worker_s;
private:
	std::string ip;
	int port;
	//int listenfd;
	Sock listen_s;
};

#endif
