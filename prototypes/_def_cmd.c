#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "util_str.h"
#include "util_which.h"
#include "util_env.h"
#include "util_path.h"
#include "util_parser.h"

#define OUTEND 0
#define INEND  1

int run_piped_cmds(char *cmdout, char *cmdin)
{
	int pipe_fd[2], writer_fd, reader_fd;

	/* tokenize cmdout */
	/* tokenize cmdout */

	reader_fd = fork();
	if (reader_fd == 0)
	{
		pipe(pipe_fd);

		writer_fd = fork();
		if ((writer_fd) == 0)
		{
			close(pipe_fd[OUTEND]);
			dup2(pipe_fd[INEND], STDOUT_FILENO);
			/* execve(); */
		}

	}
	else if (reader_fd < 0)
	{
		/* fork error */
	}

	return (0);
}

int setup_cmd_chain(char *first, char *second, int sep)
{
	switch (sep)
	{
		case BAR:
			/* create and run piped commands */
			break;
		default:
			/* ignore other forms, run commands in sequence */
	}
	return (0);
}

int process_cmds(char **cmds)
{
	/* get top level commands */
	/* set up pipes and logical chains */
	/* get second level commands */
	/* setup fd redirs */
	/* execute cmd/s */
	return (0);
}
