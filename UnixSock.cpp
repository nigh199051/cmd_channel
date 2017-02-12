#include"UnixSock.h"

UnixSock::UnixSock()
{
	sock=socket(AF_UNIX,SOCK_STREAM,0);
}

UnixSock::UnixSock(int fd)
{
	sock=fd;
}

int UnixSock::Bind(std::string sockfile)
{
	unlink(sockfile.c_str());
	sockaddr_un local;
	local.sun_family=AF_UNIX;
	memcpy(local.sun_path,sockfile.c_str(),sockfile.length());
	
	return bind(sock,(sockaddr*)&local,sizeof(sockaddr));
}

int UnixSock::Connect(std::string sockfile)
{
	sockaddr_un remote;
	remote.sun_family=AF_UNIX;
	memset(remote.sun_path,0,sizeof(remote.sun_path));
	memcpy(remote.sun_path,sockfile.c_str(),strlen(sockfile.c_str()));	
	
	return connect(sock,(sockaddr*)&remote,sizeof(sockaddr_un));
}

UnixSock UnixSock::Accept(sockaddr* remote,socklen_t *len)
{

	int handlefd=accept(sock,remote,len);	

	UnixSock handle_sock(handlefd);

	return handle_sock;
}

