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

/* void run_cmd(); */
/* int run_redir(char *cmd, int sep); */
/* int run_separ(char *cmd, int sep) */
/* { */
/* 	switch (sep) */
/* 	{ */
/* 		case (SCOL): */
/* 			return (1); */
/* 		case (BAR): */
/* 			return (1); */
/* 		case (BBAR): */
/* 			return (1); */
/* 		case (AND): */
/* 			return (1); */
/* 		case (AAND): */
/* 			return (1); */
/* 		default: */
/* 	} */

/* 	return (0); */
/* } */

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

/* void proc_separs(char **cmds, int (*separators)[]) */
/* { */
/* 	char *cmd, *copy, *sep, **redir; */
/* 	int (*redirectors)[]; */
/* 	redirectors = malloc(sizeof(int) * MAX_CMDS); */
/* 	for (int c = 0; cmds[c] != NULL; c++) */
/* 	{ */
/* 		sep = get_sep_str((*separators)[c + 1]); */
/* 		copy = str_dup(cmds[c]); */
/* 		cmd = str_strip(copy); */
/* 		printf("%s", sep); */
/* 		redir = serializer(cmd, redirectors, REDIR); */
/* 		proc_redirs(redir, redirectors); */
/* 		free(copy); */
/* 		free(cmd); */
/* 		free(*redir); */
/* 		free(redir); */
/* 	} */
/* 	free(redirectors); */
/* } */

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

int proc_cmds(char *line)
{
	char *separ, *redir, *symbol, *cmd, **cmd_tokens, *cmdpath;
	int sep, red;

	/*
	 * determine the kind of execution
	 * pass the separation onto the redirector
	 *     set up the redirections
	 * execute
	 */

	while ((separ = get_separation(line, &sep)))
	{
		separ = str_strip(separ);

		cmd = get_redirection(separ, &red);
		cmd = str_dup(cmd);
		cmd_tokens = get_cmd(cmd, &cmdpath);
		print_cmd(cmdpath, cmd_tokens);

		symbol = get_redir_str(red);
		while ((redir = get_redirection(separ, &red)))
		{
			printf("%s [%s] ", redir, symbol);
			symbol = get_redir_str(red);
		}

		symbol = get_sep_str(sep);
		printf(" [%s] ", symbol);

		free(cmdpath);
		free(*cmd_tokens);
		free(cmd_tokens);
		free(separ);

		printf("\n");
	}

	return (0);
}
