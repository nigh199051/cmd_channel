#include"pkg_parser.h"

pkg_parser::pkg_parser(int mag)
{
	magic=mag;
}

pkg_body pkg_parser::unpack(char* pkg,int len)
{

	pkg_body pbody;
/*
	int magic=pkg[0];

	switch(magic)
	{
		case '>':
		{
			memcpy(pbody.buff,pkg+1,len-1);
			break;
		}
		case 1://1×÷Îªdebug
		{
			general_pkg* pgpkg=(general_pkg*)pkg;
			pkg_body tmp=pgpkg->body;
			break;
		}
	}
*/
	return pbody;
}

general_pkg pkg_parser::pack(char* buff,const char* from_ip,int from_fd,int len)
{
	general_pkg gpkg;
	gpkg.hdr.magic=magic;
	gpkg.hdr.len=len;
	memcpy(gpkg.hdr.from_ip,from_ip,strlen(from_ip));
	gpkg.hdr.from_fd=from_fd;
	memcpy(gpkg.body.buff,buff,len);

	return gpkg;
}





