/**********************************************************************
*用红黑树保存所有的连接状态，一组连接状态定义为<socket句柄，对端IP>
 * author:selfzhang
 * date:2017-02-04
* ********************************************************************/
#ifndef CONN_STATUS_H
#define CONN_STATUS_H 

#include<string>
#include<map>
#include<vector>

class conn_status
{
public:
	conn_status();
	std::vector<int> get_fd_by_ip(std::string ip);
	std::string get_ip_by_fd(int fd);
	void push_ip_fd_pair(std::string ip, int fd);
	void pop_by_ip(std::string ip);
	void pop_by_fd(int fd);
	std::map<int,std::string> dump_ip_fd_mapper();
private:
	std::map<int,std::string> ip_fd_mapper;
};

#endif
