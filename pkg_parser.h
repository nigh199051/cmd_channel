#ifndef PKG_PARSER_H
#define PKG_PARSER_H

#include<string.h>

#define F_LEN 2048

typedef struct __general_cmd
{
	char magic;
	char cmd[F_LEN];	
	char para[F_LEN];
	char args[F_LEN];
}general_cmd;

class pkg_parser
{
public:
	pkg_parser();
	general_cmd do_parse(char* pkg,int len);
};

#endif
