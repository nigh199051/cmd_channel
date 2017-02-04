#include"mux.h"
#include"handler.h"

/*
static void mux::handlefd_handler(int fd,short type0,void* arg)
{
	mux* p=(mux*)arg;
	char buff[1024]={0};
	read(fd,buff,1024);
	write(fd,buff,1024);
}

static void mux::listenfd_handler(int fd,short type0,void* arg)
{
	mux* p=(mux*)arg;
	int handlefd=accept(fd,NULL,NULL);
	set_nonblock(handlefd);
	p->emgr->add_event(handlefd,EV_READ|EV_PERSIST,mux::handlefd_handler,arg);
}
static void mux::set_nonblock(int fd)
{
	int flags=fcntl(fd,F_GETFL,0);
	flags|=O_NONBLOCK;
	fcntl(fd,F_SETFL,flags);
}
*/
mux::mux(std::string,int port)
{
	this->ip=ip;
	this->port=port;
	emgr=new event_mgr();
	cs=new conn_status();
}


void mux::sock_init()
{
/*
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	//set_nonblock(listenfd);
	int flags=fcntl(listenfd,F_GETFL,0);
	flags|=O_NONBLOCK;
	fcntl(listenfd,F_SETFL,flags);

	sockaddr_in local;
	local.sin_family=AF_INET;
	//local.sin_addr.s_addr=inet_addr(ip.c_str());
	local.sin_addr.s_addr=htonl(INADDR_ANY);
	local.sin_port=htons(port);

	int reuse=1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int));

	bind(listenfd,(sockaddr*)&local,sizeof(local));
	listen(listenfd,1024);
*/
	listen_s.Bind("0.0.0.0",9699);
	listen_s.set_nonblock();
	listen_s.set_reuse();
	listen_s.Listen();
}

void mux::do_it()
{
	sock_init();

	Event e;
	e.fd=listen_s.get_fd();
	e.type0=EV_READ|EV_PERSIST;
	e.handler=handler::listenfd_handler;
	e.arg=(void*)this;
	emgr->add_event(e);

	//emgr->add_event(listenfd,EV_READ|EV_PERSIST,handler::listenfd_handler,this);
	Event sig_e;
	sig_e.fd=2;
	sig_e.type0=EV_SIGNAL|EV_PERSIST;
	sig_e.handler=handler::sig_handler;
	sig_e.arg=(void*)this;
	//emgr->add_sig_event(2,handler::sig_handler,this);
	
	emgr->add_sig_event(sig_e);
	emgr->run();
}
