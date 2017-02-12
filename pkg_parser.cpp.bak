#include"pkg_parser.h"

pkg_parser::pkg_parser()
{

}

general_cmd pkg_parser::do_parse(char* pkg,int len)
{
	//terminal pkg
	general_cmd tc;
	//
	int phase=0;
	int j=0;
	memset(&tc,'\0',sizeof(general_cmd));
	tc.magic=pkg[0];
	for(int i=1;i<len;i++)
	{
		if(pkg[i]=='\n')
		{
			break;
		}
		if(j==0&&pkg[i]==' ')
		{
			continue;
		}
		switch(phase)
		{
			case 0:{
				//cmd	
				if(pkg[i]!=' ')
				{
					tc.cmd[j++]=pkg[i];
				}
				else
				{
					tc.cmd[j]=0;
					phase+=1;
					j=0;
				}
				break;
			}
			case 1:{
				//para	
				if(pkg[i]!=' ')
				{
					tc.para[j++]=pkg[i];
				}
				else
				{
					tc.para[j]=0;
					phase+=1;
					j=0;
				}
				break;
			}
			case 2:{
				//args	
				if(pkg[i]!=' ')
				{
					tc.args[j++]=pkg[i];
				}
				else
				{
					tc.args[j]=0;
					phase+=1;
					j=0;
				}
				break;
			}
			default:{
				break;
			}
		}//switch 
	}//for
	tc.args[j]=0;

	return tc;
}
