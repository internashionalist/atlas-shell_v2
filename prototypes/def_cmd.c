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

#define OUTEND 0
#define INEND  1

/* int run_piped_cmds(char *cmdout, char *cmdin) */
/* int setup_cmd_chain(char *first, char *second, int sep) */
/* void run_cmd(); */
/* int run_separ(char *cmd, int sep) */
/* void proc_separs(char **cmds, int (*separators)[]) */

void proc_redirs(char **cmd, int (*redirectors)[])
{
	char *redir;

	printf("\t%s\n", cmd[0]);
	for (int r = 1; cmd[r] != NULL; r++)
	{
		redir = get_redir_str((*redirectors)[r]);
		printf("\t%s %s\n", redir, cmd[r]);
	}
}

char **get_cmd(char *cmd, char **cmdpath)
{
	char **cmd_tokens;

	cmd_tokens = tokenize(cmd, " ", 512);
	*cmdpath = _which(cmd_tokens[0]);

	return (cmd_tokens);
}

void run_cmd(char *cmdpath, char **cmd_tokens)
{
	int wstatus;

	switch (fork())
	{
		case -1:
			return;
		case 0:
			execve(cmdpath, cmd_tokens, NULL);
			return;
		default:
			wait(&wstatus);
	}
}

void print_cmd(char *cmdpath, char **cmd_array)
{
	int i = 1;

	printf("\n");
	printf("<%s> ", cmdpath);
	while (cmd_array[i] != NULL)
	{
		printf("<%s> ", cmd_array[i]);
		i++;
	}
}

int redir_left(char *filename, int append)
{
	int fdesc;
	int fmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	int fflags = O_CREAT | O_WRONLY | append;

	fdesc = open(filename, fflags, fmode);

	dup2(fdesc, STDOUT_FILENO);

	return (fdesc);
}

void setup_redir(char *filename, int *fdesc, int code)
{
	if (*fdesc > -1)
		close(*fdesc);

	filename = str_strip(filename);
	/* dprintf(STDERR_FILENO, "%s\n", filename); */

	switch (code)
	{
	case (LOUT):
		*fdesc = redir_left(filename, 0);
		break;
	case (LLOUT):
		*fdesc = redir_left(filename, O_APPEND);
		break;
	}

	free(filename);
}

int determine_logic(int code, int composite, int last)
{
       switch (code)
       {
       case (BBAR):
               return (composite || last);
       case (AAND):
               return (composite && last);
       default:
               return (last);
       }
}

int proc_cmds(char *line)
{
	char *separ, *filename, *cmd, **cmd_tokens, *cmdpath;
	int sep, red, fdesc = -1;

	while ((separ = get_separation(line, &sep)))
	{
		separ = str_dup(separ);
		cmd = get_redirection(separ, &red);
		cmd = str_dup(cmd);

		do {
			if (red > -1 )
				setup_redir(filename, &fdesc, red);
		} while ((filename = get_redirection(separ, &red)));

		cmd_tokens = get_cmd(cmd, &cmdpath);
		run_cmd(cmdpath, cmd_tokens);

		if (fdesc > -1)
			close(fdesc);
		free(cmd);
		free(cmdpath);
		free(cmd_tokens);
		free(separ);
	}

	return (0);
}
