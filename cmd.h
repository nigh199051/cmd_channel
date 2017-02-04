#ifndef CMD_H
#define CMD_H

typedef struct __terminal_cmd
{
	char cmd[128];	
	char para[2048];
	char args[2048];
}term_cmd;

#endif
