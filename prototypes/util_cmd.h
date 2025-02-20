#ifndef _CMDS_
#define _CMDS_

#define MAX_CMDS 2048

typedef struct _cmd_packet {
	int io;
	char *instr;
} cmd_packet;

int proc_cmds(char *cmdline);

#endif /* _CMDS_ */
