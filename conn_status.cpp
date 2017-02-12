#include "conn_status.h"
#include<iostream>

conn_status::conn_status()
{
	std::cout<<"biu"<<std::endl;	
}

void conn_status::push_ip_fd_pair(std::string ip,int fd)
{
	ip_fd_mapper[fd]=ip;
}

std::string conn_status::get_ip_by_fd(int fd)
{
	if(ip_fd_mapper.find(fd)!=ip_fd_mapper.end())
	{
		return ip_fd_mapper[fd];	
	}

	return "";
}

std::vector<int> conn_status::get_fd_by_ip(std::string ip)
{
	std::vector<int> tmp;
	std::map<int,std::string>::iterator iter;
	for (iter=this->ip_fd_mapper.begin();iter!=this->ip_fd_mapper.end();iter++)
	{
		if(iter->second == ip)
		{
			tmp.push_back(iter->first);	
		}
	}
	return tmp;
}

std::map<int,std::string> conn_status::dump_ip_fd_mapper()
{
	return this->ip_fd_mapper;
}


void conn_status::pop_by_fd(int fd)
{
	std::map<int,std::string>::iterator iter=ip_fd_mapper.find(fd);
	if(iter != ip_fd_mapper.end())
	{
		ip_fd_mapper.erase(iter);
	}
}

void conn_status::pop_by_ip(std::string ip)
{
	std::map<int,std::string>::iterator iter;
	for(iter=ip_fd_mapper.begin();iter!=ip_fd_mapper.end();iter++)
	{
		if(iter->second==ip)
		{
			ip_fd_mapper.erase(iter);
			return;
		}
	}
}
