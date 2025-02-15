#include "util_parser.h"
#include "util_cmd.h"
#include "util_str.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int c, char **args)
{
	int cmdfile, filesize = 2048;
	char *cmdtext, *cmdline;

	if (c < 2)
		return (1);

	cmdfile = open(args[1], O_RDONLY);
	cmdtext = malloc(sizeof(char) * filesize);
	strmem_init(&cmdtext, filesize, 0);
	read(cmdfile, cmdtext, filesize);

	printf("\n%s\n", cmdtext);

	cmdline = read_line(cmdtext);
	while (cmdline)
	{
		proc_cmds(cmdline);
		cmdline = read_line(NULL);
	}

	free(cmdline);
	free(cmdtext);

	return (0);
}
