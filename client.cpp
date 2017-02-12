#include"UnixSock.h"
#include<iostream>
#include<errno.h>
#include<stdio.h>
using namespace std;

int main()
{
	UnixSock us;
	int ret=us.Connect("/tmp/worker.so");
	if(ret<0)
	{
		perror("connect failed:");
		return 0;
	}
	ret=us.Write("hello",5);
	char buff[1024]={0};
	ret=us.Read(buff,1024);
	cout<<buff<<endl;
	return 0;
}
