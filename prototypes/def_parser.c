#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util_parser.h"

// tokenize
// execute

int check_io_str(char *string, int pos)
{
	switch (string[pos])
	{
		case '>':
			if (string[pos + 1] == '>')
				return (LLOUT);
			else
				return (LOUT);
		case '<':
			if (string[pos + 1] == '<')
				return (RRIN);
			else
				return (RIN);
		default:
			return (-1);
	}
}

int check_sep_str(char *string, int pos)
{
	switch (string[pos])
	{
		case ';':
			return (SCOL);
		case '|':
			if (string[pos + 1] == '|')
				return (BBAR);
			else
				return (BAR);
		case '&':
			if (string[pos + 1] == '&')
				return (AAND);
			else
				return (AND);
		default:
			return (-1);
	}
}

char **io_serializer(char *cmdstr, int **partitions)
{
	(void) cmdstr;
	(void) partitions;

	return (NULL);
}

/*
 * splits a string along the ;, |, ||, and && characters
 */

char **cmd_serialiser(char *cmdstr, int **partitions)
{
	char **cmds = malloc(sizeof(void *) * 1024);
	char *delims = ";|&";
	int c = 0, p = 0, sep;

	while (cmdstr[c] != '\0')
	{
		sep = check_sep_str(cmdstr, c);
		if (sep > -1);
		{
			(*partitions)[p] = sep;
			if (p == 0)
				cmds[p] = strtok(cmdstr, delims);
			else
				cmds[p] = strtok(NULL, delims);
			p++;
		}
		c++;
	}
	return (cmds);
}

char **cmd_io(char *cmdstr)
{
	char **io_cmd;
	char *io_inst[] = {"<", "<<", ">", ">>"};
	char *delims = "<>";
	int redir, c = 0;

	while (cmdstr[c] != '\0')
	{
		redir = check_io_str(cmdstr, c);
		if (redir > -1)
			break;
		c++;
	}

	if (redir > -1)
	{
		io_cmd = malloc(sizeof(void *) * 4);
		io_cmd[0] = strtok(cmdstr, delims);
		io_cmd[1] = io_inst[redir];
		io_cmd[2] = strtok(NULL, delims);
		io_cmd[3] = NULL;
	}
	else
	{
		io_cmd = malloc(sizeof(void *) * 2);
		io_cmd[0] = cmdstr;
		io_cmd[1] = NULL;
	}

	return (io_cmd);
}

//tokenizer
