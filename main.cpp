#include"mux.h"
#include<iostream>
#include<string>
#include<map>
#include"event_mgr.h"
#include<sys/socket.h>
#include<unistd.h>
#include"conn_status.h"

using namespace std;


int main()
{
	//conn_status cs;
	//cs.push_ip_fd_pair("192.168.0.1",1);
	//cout<<cs.get_fd_by_ip("192.168.0.1")<<endl;
	mux m("0.0.0.0",9699);
	m.do_it();

	//m.cs->push_ip_fd_pair("192.168.0.1",1);
	//cout<<m.cs->get_fd_by_ip("192.168.0.1");

	return 0;	
}

