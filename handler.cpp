#include"handler.h"
#include"mux.h"


void handler::sig_handler(int sig,short type0,void* arg)
{

	std::cout<<"signal received"<<std::endl;
	/*
	mux* p=(mux*)arg;
	std::map<std::string,int> tmp=p->cs->dump_ip_fd_mapper();
	for(std::map<std::string,int>::iterator it=tmp.begin();it!=tmp.end();it++)
	{
		//std::cout<<it->first<<" "<<it->second<<std::endl;
		
		std::cout<<"push to ip="<<it->first<<" fd="<<it->second<<std::endl;
		write(it->second,"hello",6);
	}
	*/
}
void handler::handlefd_handler(int fd,short type0,void* arg)
{
/*
	int** arr=(int**)arg;
	mux* p=(mux*)arr[0];
	event* e=(event*)arr[1];
	//mux* p=(mux*)arg;
	char buff[1024]={0};
	int ret=read(fd,buff,1024);

	write(fd,buff,1024);
	if(ret==0||ret<0)
	{
		//p->cs->pop_ip();
		std::cout<<"client closed socket"<<std::endl;
		close(fd);
		p->emgr->del_event(e);
	}
*/
//
	//int** arr=(int**)arg;
	mux* p=(mux*)arg;
	//event* e=(event*)arr[1];
	
	char buff[2048]={0};
	char pkg[2048]={0};

	int ret=read(fd,buff,2048);
	
	if (ret >0)
	{
		pkg_parser pp;
		general_cmd gcmd;
		gcmd=pp.do_parse(buff,2048);
		switch(gcmd.magic)
		{
			case 't':{
				sprintf(pkg,"{\"cmd\":\"%s\",\"para\":\"%s\",\"args\":\"%s\",\"padding\":\"\",\"len\":0}",gcmd.cmd,gcmd.para,gcmd.args);
				std::map<int,std::string> tmp=p->cs->dump_ip_fd_mapper();
				for(std::map<int,std::string>::iterator it=tmp.begin();it!=tmp.end();it++)
				{
					if(fd!=it->first)
					{
						std::cout<<"push to ip="<<it->second<<" fd="<<it->first<<std::endl;
						std::cout<<write(it->first,pkg,1056)<<std::endl;
					}
				}
				break;
			}
			case 'c':{
				write(fd,buff+1,2048);
				break;
			}
		}
	}
	else
	{
		std::cout<<"client closed socket"<<std::endl;
		close(fd);
		Event e;
		e.fd=fd;
		e.type0=EV_READ;
		p->emgr->del_event(e);
		p->cs->pop_by_fd(fd);
	}
//
	
	
};
void handler::listenfd_handler(int fd,short type0,void* arg)
{
	//int** pack=(int**)arg;
	mux* p=(mux*)arg;
	//mux* p=(mux*)arg;
	sockaddr_in remote;
	socklen_t len=sizeof(remote);
	int handlefd=accept(fd,(sockaddr*)&remote,&len);
	char* ip=inet_ntoa(remote.sin_addr);
	//std::cout<<handlefd<<" "<<fd<<std::endl;
	//std::cout<<p->cs<<std::endl;
	p->cs->push_ip_fd_pair(ip,handlefd);
	set_nonblock(handlefd);
	Event e;
	e.fd=handlefd;
	e.type0=EV_READ|EV_PERSIST;
	e.handler=handler::handlefd_handler;
	e.arg=arg;
	p->emgr->add_event(e);
	std::map<int,std::string> tmp=p->cs->dump_ip_fd_mapper();
	for(std::map<int,std::string>::iterator it=tmp.begin();it!=tmp.end();it++)
	{
		std::cout<<it->first<<" "<<it->second<<std::endl;
	}
};
void handler::set_nonblock(int fd)
{
	int flags=fcntl(fd,F_GETFL,0);
	flags|=O_NONBLOCK;
	fcntl(fd,F_SETFL,flags);
};
