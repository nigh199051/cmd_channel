#ifndef PKG_PARSER_H
#define PKG_PARSER_H

#include<string.h>

#define BODY_LEN 2048
#define PKG_LEN 2088

/*包头先定义一个字段magic，用于区分协议,以后再扩充*/
typedef struct __pkg_header
{
	char magic;
	char from_ip[16];
	int from_fd;
	int len;
}pkg_header;

typedef struct __pkg_body
{
	char buff[BODY_LEN];
}pkg_body;

typedef struct __general_pkg
{
	pkg_header hdr;		//包头40B+包体2048B=2080B
	pkg_body body;
}general_pkg;

class pkg_parser
{
public:
	pkg_parser(int mag=0);
	//int pack_and_send(char* buff,int len);
	//int unpack_and_recv(char* buff,int* len);
	general_pkg pack(char* buff,const char* from_ip,int from_fd,int len);
	pkg_body unpack(char* buff,int len);	
private:
	int magic;
};

#endif
