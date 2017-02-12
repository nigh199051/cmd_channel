#ifndef HANDLER_H
#define HANDLER_H
#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
#include<fcntl.h>
#include<event.h>
#include<map>
#include"pkg_parser.h"

class handler
{
public:
	static void listenfd_handler(int fd,short type0,void* arg);
	static void handlefd_handler(int fd,short type0,void* arg);
	static void worker_handler(int fd,short type0,void* arg);
	static void set_nonblock(int fd);	
	static void sig_handler(int fd,short type0,void* arg);
};

#endif
