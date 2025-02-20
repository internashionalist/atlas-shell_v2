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
	char *cmdtext, *cmdline, *cleanline;

	if (c < 2)
		return (1);

	cmdfile = open(args[1], O_RDONLY);
	cmdtext = malloc(sizeof(char) * filesize);
	strmem_init(&cmdtext, filesize, 0);
	read(cmdfile, cmdtext, filesize);

	cmdline = read_line(cmdtext);
	while (cmdline)
	{
		cleanline = remove_comment(cmdline, "#");
		if (cleanline)
			proc_cmds(cleanline);
		free(cleanline);
		cmdline = read_line(NULL);
	}

	free(cmdline);
	free(cmdtext);
	return (0);
}
