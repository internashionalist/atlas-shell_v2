#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "util_which.h"
#include "util_env.h"

#define READ_END 0
#define WRITE_END  1

extern char **environ;

int is_child(int fd)
{
	if (fd == 0)
		return (1);
	return (0);
}

char **prep_cmd(char *cmdstr)
{
	char **cmd;

	cmd = malloc(sizeof(char *) * 2);
	cmd[0] = _which(cmdstr);
	cmd[1] = NULL;

	return (cmd);
}

int proc_cmds(char **cmds, int c)
{
	int linker[2], readin, writeout;
	char **cmd = NULL;

	readin = STDIN_FILENO;

	for (int i = 0; i < c; i++)
	{
		pipe(linker);

		writeout = linker[WRITE_END];
		if (i + 1 == c)
			writeout = STDOUT_FILENO;

		cmd = prep_cmd(cmds[i]);

		if (is_child(fork()))
		{
			close(linker[READ_END]);

			dup2(readin, STDIN_FILENO);
			dup2(writeout, STDOUT_FILENO);

			execve(cmd[0], cmd, environ);
		}

		wait(NULL);
		close(readin);
		close(linker[WRITE_END]);
		readin = linker[READ_END];
		free(cmd[0]);
		free(cmd);
	}

	wait(NULL);
	close(readin);

	return (-1);
}

int main(int a, char **args)
{
	init_env();

	proc_cmds(&args[1], a - 1);

	reset_env();

	exit(EXIT_SUCCESS);
}
