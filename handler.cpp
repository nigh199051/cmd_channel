#include"handler.h"
#include"mux.h"
#include"pkg_parser.h"
#include<string.h>
#include<errno.h>

#include<iostream>


void handler::sig_handler(int sig,short type0,void* arg)
{
	std::cout<<"signal received"<<std::endl;
}

void handler::worker_handler(int fd,short type0,void* arg)
{
	mux* p=(mux*)arg;
	
	char buff[PKG_LEN]={0};
	char pkg[BODY_LEN]={0};

	int sum=0;
	bool ok=true;

	while(sum<PKG_LEN)
	{
		int ret=read(fd,buff,PKG_LEN);
		if(ret>0)
		{
			sum+=ret;
		}
		else if(ret<0&&errno==EAGAIN)
		{
			break;
		}
		else if(ret==0)
		{
			break;
		}
		else if(ret<0)
		{
			ok=false;
			break;
		}
	}

	if(ok)	
	{
		std::cout<<buff<<std::endl;	
	}
	else
	{
		close(fd);
		Event e;
		e.fd=fd;
		e.type0=EV_READ;
		p->emgr->del_event(e);
		p->cs->pop_by_fd(fd);
		return;
	}
}

void handler::handlefd_handler(int fd,short type0,void* arg)
{
	mux* p=(mux*)arg;
	//event* e=(event*)arr[1];
	
	char buff[PKG_LEN]={0};
	char pkg[BODY_LEN]={0};

	int sum=0;
	bool ok=true;

	while(sum<PKG_LEN)
	{
		int ret=read(fd,buff,PKG_LEN);
		if(ret>0)
		{
			sum+=ret;
		}
		else if(ret<0&&errno==EAGAIN)
		{
			break;
		}
		else if(ret==0)
		{
			break;
		}
		else if(ret<0)
		{
			ok=false;
			break;
		}
	}

	if(ok)	
	{
		//pkg_parser pp;
		//general_pkg gpkg=pp.pack(buff,p->cs->get_ip_by_fd(fd).c_str(),fd,sum);
		//解包完交给worker
		//handle pkg
		//p->worker_s.Write((char*)&gpkg,sizeof(general_pkg));
		p->worker_s.Write(buff,strlen(buff));
		//write(p->worker_s.get,(char*)&gpkg,sizeof(general_pkg));
	}
	else
	{
		close(fd);
		Event e;
		e.fd=fd;
		e.type0=EV_READ;
		p->emgr->del_event(e);
		p->cs->pop_by_fd(fd);
		return;
	}

	
/*
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
			default:{
				FILE* fp=fopen("index.html","r");
				char content[1024]={0};
				fread(content,1,1024,fp);
				fclose(fp);
				sprintf(pkg,"HTTP/1.0 200 OK\r\nContent-Type:text/html\r\nContent-Length:%d\r\n\r\n%s\r\n\r\n",strlen(content),content);
				write(fd,pkg,2048);
				close(fd);
				Event e;
				e.fd=fd;
				e.type0=EV_READ;
				p->emgr->del_event(e);
				p->cs->pop_by_fd(fd);
				break;
			}
		}
	}
	else
	{
		//std::cout<<"client closed socket"<<std::endl;
		close(fd);
		Event e;
		e.fd=fd;
		e.type0=EV_READ;
		p->emgr->del_event(e);
		p->cs->pop_by_fd(fd);
	}
//
*/	
	
}
void handler::listenfd_handler(int fd,short type0,void* arg)
{
	//int** pack=(int**)arg;
	mux* p=(mux*)arg;
	sockaddr_in remote;
	socklen_t len=sizeof(remote);
	int handlefd=accept(fd,(sockaddr*)&remote,&len);
	char* ip=inet_ntoa(remote.sin_addr);
	p->cs->push_ip_fd_pair(ip,handlefd);
	set_nonblock(handlefd);
	Event e;
	e.fd=handlefd;
	e.type0=EV_READ|EV_PERSIST;
	e.handler=handler::handlefd_handler;
	e.arg=arg;
	p->emgr->add_event(e);
	std::map<int,std::string> tmp=p->cs->dump_ip_fd_mapper();
	//std::cout<<tmp.size()<<std::endl;
	/*
	for(std::map<int,std::string>::iterator it=tmp.begin();it!=tmp.end();it++)
	{
		std::cout<<it->first<<" "<<it->second<<std::endl;
	}
	*/
};
void handler::set_nonblock(int fd)
{
	int flags=fcntl(fd,F_GETFL,0);
	flags|=O_NONBLOCK;
	fcntl(fd,F_SETFL,flags);
};

