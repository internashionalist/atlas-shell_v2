#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> /* file mode_t defs */
#include "util_str.h"
#include "util_cmd.h"
#include "util_which.h"
#include "util_env.h"
#include "util_path.h"
#include "util_parser.h"

#define READ_END  0
#define WRITE_END 1

char **get_cmd(char *cmd, char **cmdpath)
{
	char **cmd_tokens;

	cmd_tokens = tokenize(cmd, " ", 512);
	*cmdpath = _which(cmd_tokens[0]);

	return (cmd_tokens);
}

int run_cmd(char *cmdpath, char **cmd_tokens, int code, int fdesc)
{
	int wstatus, writeout, linker[2];
	static int readin = STDIN_FILENO;

	pipe(linker);
	if (fdesc != STDOUT_FILENO)
		writeout = fdesc;
	else if (code == BAR)
		writeout = linker[WRITE_END];
	else
		writeout = STDOUT_FILENO;

	switch (fork())
	{
		case -1:
			return (0);
		case 0:
			close(linker[READ_END]);
			dup2(readin, STDIN_FILENO);
			dup2(writeout, STDOUT_FILENO);
			execve(cmdpath, cmd_tokens, environ);
			return (0);
		default:
			wait(&wstatus);
			if (writeout != STDOUT_FILENO)
				close(writeout);
			if (readin != STDIN_FILENO)
				close(readin);
			if (code == BAR)
				readin = linker[READ_END];
			else
				readin = STDIN_FILENO;
	}

	if (WIFEXITED(wstatus) && !WEXITSTATUS(wstatus))
		wstatus = 1;
	else
		wstatus = 0;

	return (wstatus);
}

int redir_left(char *filename, int append)
{
	int fdesc;
	int fmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	int fflags = O_CREAT | /*O_CLOEXEC |*/ O_WRONLY | append;

	fdesc = open(filename, fflags, fmode);
	/* fcntl(fdesc, F_SETFD, FD_CLOEXEC); */
	/* fdesc = fcntl(fdesc, F_DUPFD_CLOEXEC); */

	dup2(fdesc, STDOUT_FILENO);

	return (fdesc);
}

int setup_redir(char *filename, int fdesc, int code)
{
	if (fdesc != STDOUT_FILENO)
		close(fdesc);

	filename = str_strip(filename);

	switch (code)
	{
	case (LOUT):
		fdesc = redir_left(filename, 0);
		break;
	case (LLOUT):
		fdesc = redir_left(filename, O_APPEND);
		break;
	default:
		fdesc = -1;
	}

	free(filename);

	return (fdesc);
}

int resolve_logic(int cmdexit, int operand)
{
	switch (operand)
	{
	case (BBAR):
		if (cmdexit)
			return (1);
		break;
	case (AAND):
		if (!cmdexit)
			return (1);
		break;
	}
	return (0);
}

int proc_cmds(char *line)
{
	char *separ, *filename = NULL, *cmd, **cmd_tokens, *cmdpath;
	int sep, red, fdesc = -1, cmdexit, skip = 0;

	while ((separ = get_separation(line, &sep)))
	{
		fdesc = STDOUT_FILENO;
		separ = str_dup(separ);
		cmd = get_redirection(separ, &red);
		cmd = str_dup(cmd);

		do {
			if (red > -1 )
				fdesc = setup_redir(filename, fdesc, red);
		} while ((filename = get_redirection(separ, &red)));

		cmd_tokens = get_cmd(cmd, &cmdpath);

		if (!skip)
			cmdexit = run_cmd(cmdpath, cmd_tokens, sep, fdesc);

		skip = resolve_logic(cmdexit, sep);

		free(cmd);
		free(cmdpath);
		free(cmd_tokens);
		free(separ);
	}

	return (0);
}
