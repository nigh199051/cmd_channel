#include<iostream>
#include<event.h>
#include<sys/socket.h>
using namespace std;

struct event ev;
struct timeval tv;
struct event_base *base;

int listenfd;
void time_cb(int fd,short event,void* argc)
{
	cout<<"timer wake up"<<endl;
	event_add(&ev,&tv);
}

void fifo_read(evutil_socket_t tfd,short event,void* arg)
{
	if(tfd==listenfd)
	{
		int fd=accept(listenfd,NULL,NULL);
		evutil_make_socket_nonblocking(fd);
		struct event *tmp_event=event_new(base,fd,EV_READ,fifo_read,NULL);
		event_add(tmp_event,NULL);
		event_add(&ev,NULL);
		return;
	}

	char buff[1024]={0};
	read(tfd,buff,1024);
	write(tfd,buff,1024);
	close(tfd);
	event_add(&ev,NULL);
}

int main()
{

	listenfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=INADDR_ANY;
	local.sin_port=htons(3344);

	bind(listenfd,(struct sockaddr*)&local,sizeof(local));

	listen(listenfd,5);

	base=event_init();

	evutil_make_socket_nonblocking(listenfd);
	event_set(&ev,listenfd,EV_READ|EV_PERSIST,fifo_read,&ev);
	event_add(&ev,NULL);

	while(1)
	{
		event_dispatch();
		/*
		int handlefd=accept(listenfd,NULL,NULL);
		char buff[1024]={0};
		read(handlefd,buff,1024);
		write(handlefd,buff,1024);
		close(handlefd);
		*/
	}
	return 0;
}
