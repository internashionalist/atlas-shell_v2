#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "util_str.h"
#include "util_cmd.h"
#include "util_which.h"
#include "util_env.h"
#include "util_path.h"
#include "util_parser.h"

#define OUTEND 0
#define INEND  1

/* int run_piped_cmds(char *cmdout, char *cmdin) */
/* { */
/* 	int pipe_fd[2], writer_fd, reader_fd; */

/* 	/1* tokenize cmdout *1/ */
/* 	/1* tokenize cmdout *1/ */

/* 	reader_fd = fork(); */
/* 	if (reader_fd == 0) */
/* 	{ */
/* 		pipe(pipe_fd); */

/* 		writer_fd = fork(); */
/* 		if ((writer_fd) == 0) */
/* 		{ */
/* 			close(pipe_fd[OUTEND]); */
/* 			dup2(pipe_fd[INEND], STDOUT_FILENO); */
/* 			/1* execve(); *1/ */
/* 		} */

/* 	} */
/* 	else if (reader_fd < 0) */
/* 	{ */
/* 		/1* fork error *1/ */
/* 	} */

/* 	return (0); */
/* } */

/* int setup_cmd_chain(char *first, char *second, int sep) */
/* { */
/* 	switch (sep) */
/* 	{ */
/* 		case BAR: */
/* 			/1* create and run piped commands *1/ */
/* 			break; */
/* 		default: */
/* 			/1* ignore other forms, run commands in sequence *1/ */
/* 	} */
/* 	return (0); */
/* } */

void run_cmd();

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

void proc_separs(char **cmds, int (*separators)[])
{
	char *cmd, *copy, *sep, **redir;
	int (*redirectors)[];

	(void) redir;

	redirectors = malloc(sizeof(int) * MAX_CMDS);

	for (int c = 0; cmds[c] != NULL; c++)
	{
		sep = get_sep_str((*separators)[c + 1]);
		copy = str_dup(cmds[c]);
		cmd = str_strip(copy);

		printf("%s ", sep);

		redir = serializer(cmd, redirectors, REDIR);
		proc_redirs(redir, redirectors);

		free(copy);
		free(cmd);
		free(*redir);
		free(redir);
	}

	printf("----------------\n");

	free(redirectors);
}

int proc_cmds(char *cmdline)
{
	int (*separators)[];
	char **cmds;

	separators = malloc(sizeof(int) * MAX_CMDS);
	cmds = serializer(cmdline, separators, SEPAR);
	proc_separs(cmds, separators);

	free(separators);
	free(*cmds);
	free(cmds);

	return (0);
}
