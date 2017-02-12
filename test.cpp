#include<iostream>
#include"UnixSock.h"
using namespace std;

int main()
{
	UnixSock us;
	us.Bind("/tmp/work.so");
	us.Listen();
	while(1)
	{
		UnixSock hs=us.Accept(NULL,NULL);
		char buff[1024]={0};
		hs.Read(buff,1024);
		hs.Write(buff,1024);
	}
	return 0;
}
