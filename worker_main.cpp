#include"UnixSock.h"
#include<iostream>
#include<stdio.h>
using namespace std;


int main()
{

	UnixSock us;

	if(us.Bind("/tmp/worker.sock")<0)
	{
		perror("bind error");
		return -1;
	}
	if(us.Listen()<0)
	{
		perror("listen error");
		return -1;
	}
	
	while(1)
	{
		UnixSock hs=us.Accept(NULL,NULL);
		cout<<"Connection established"<<endl;

		if(hs.get_fd()<0)
		{
			perror("accept error");
			break;
		}
		int ret=fork();
		if(ret==0)
		{
			char buff[1024]={0};
			int ret=hs.Read(buff,1024);
			cout<<"ret="<<ret<<endl;
			cout<<buff<<endl;
			hs.Write(buff,1024);
			//hs.Close();
			return 0;
		}
		else if(ret>0)
		{
			;
		}
		else
		{
			break;	
		}
	}

	return 0;
}
