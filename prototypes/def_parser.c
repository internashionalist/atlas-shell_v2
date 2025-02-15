#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util_parser.h"
#include "util_str.h"
#include "util_cmd.h"

// tokenize
// execute

int check_redir_chars(char *string, int pos)
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

int check_sep_chars(char *string, int pos)
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

char *get_redir_str(int code)
{
	switch (code)
	{
		case (LOUT):
			return (">");
		case (LLOUT):
			return (">>");
		case (RIN):
			return ("<");
		case (RRIN):
			return ("<<");
		default:
			return ("_");
	}
}

char *get_sep_str(int code)
{
	switch (code)
	{
		case (SCOL):
			return (";");
		case (BAR):
			return ("|");
		case (BBAR):
			return ("||");
		case (AND):
			return ("&");
		case (AAND):
			return ("&&");
		default:
			return ("_");
	}
}

int is_double_sep(int symbol)
{
	if (symbol == AAND || symbol == BBAR)
		return (1);
	return (0);
}

int is_double_redir(int symbol)
{
	if (symbol == LLOUT || symbol == RRIN)
		return (1);
	return (0);
}

char **serializer(
char *cmdstr,
int (*partitions)[],
part p)
{
	char **cmds, *copy, *delims;
	int c = 0, s = 0, split = -1, size = MAX_CMDS;
	int (*char_check)(char *, int);
	int (*is_double)(int);

	/* setup desired serialization type*/
	switch (p)
	{
		case SEPAR:
			char_check = check_sep_chars;
			is_double = is_double_sep;
			delims = ";|&";
			break;
		case REDIR:
			char_check = check_redir_chars;
			is_double = is_double_redir;
			delims = "<>";
			break;
		default:
			return (NULL);
	}

	copy = str_dup(cmdstr);
	cmds = malloc(sizeof(void *) * size);

	/* create array heads */
	cmds[s] = strtok(copy, delims);
	(*partitions)[s] = -1;
	s++;

	/* build array bodies */
	while (cmdstr[c] != '\0')
	{
		split = char_check(cmdstr, c);
		if (split > -1)
		{
			(*partitions)[s] = split;
			cmds[s] = strtok(NULL, delims);
			s++;
			if (is_double(split))
				c++;
		}
		c++;
	}

	/* close array tails */
	cmds[s] = strtok(NULL, delims);
	(*partitions)[s] = -1;
	cmds[s + 1] = NULL;

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
		redir = check_redir_chars(cmdstr, c);
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
