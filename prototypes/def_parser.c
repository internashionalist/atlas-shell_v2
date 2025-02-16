#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util_parser.h"
#include "util_str.h"
#include "util_cmd.h"

int find_string(char **strings, char *str)
{
	int index = -1;

	while (strings[index] != NULL)
		if (strings[index] == str)
			break;

	return (index);
}

int check_redir_chars(const char *string, int pos)
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

int check_sep_chars(const char *string, int pos)
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

void setup_partitioner(
part p,
int (**char_check)(const char *, int),
int (**is_double)(int),
char **delims)
{
	switch (p)
	{
	case SEPAR:
		*char_check = check_sep_chars;
		*is_double = is_double_sep;
		*delims = ";|&";
		break;
	case REDIR:
		*char_check = check_redir_chars;
		*is_double = is_double_redir;
		*delims = "<>";
		break;
	}
}

char *get_partition(char *copy, int *pos, int *sep, part kind)
{
	char *partition = NULL;
	char *delims;
	int (*char_check)(const char *, int);
	int (*is_double)(int);
	int p = 0;

	setup_partitioner(kind, &char_check, &is_double, &delims);

	while (copy[p] != '\0')
	{
		*sep = char_check(copy, p);
		p++;
		if (*sep > -1)
		{
			partition = strtok(copy, delims);
			if (is_double(*sep))
				p++;
			*pos += p;
			return (partition);
		}
	}

	partition = strtok(copy, delims);
	*pos += p;

	return (partition);
}

char *get_separation(const char *line, int *sep)
{
	static int pos = 0;
	static char *copy = NULL;
	char *separation;

	free(copy);
	copy = str_dup(&(line[pos]));

	separation = get_partition(copy, &pos, sep, SEPAR);

	if (!separation)
	{
		free(copy);
		copy = NULL;
		pos = 0;
	}

	return (separation);
}

char *get_redirection(const char *line, int *redir)
{
	static int pos = 0;
	static char *copy = NULL;
	char *redirection;

	free(copy);
	copy = str_dup(&(line[pos]));

	redirection = get_partition(copy, &pos, redir, REDIR);

	if (!redirection)
	{
		free(copy);
		copy = NULL;
		pos = 0;
	}

	return (redirection);
}
