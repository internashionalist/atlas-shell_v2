#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dec_parser.h"
#include "dec_str.h"
#include "dec_cmd.h"

int _check_redir_chars(const char *string, int pos)
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

int _check_sep_chars(const char *string, int pos)
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

int _is_double_sep(int symbol)
{
	if (symbol == AAND || symbol == BBAR)
		return (1);
	return (0);
}

int _is_double_redir(int symbol)
{
	if (symbol == LLOUT || symbol == RRIN)
		return (1);
	return (0);
}

void _setup_partitioner(
part p,
int (**char_check)(const char *, int),
int (**is_double)(int),
char **delims)
{
	switch (p)
	{
	case SEPAR:
		*char_check = _check_sep_chars;
		*is_double = _is_double_sep;
		*delims = ";|&";
		break;
	case REDIR:
		*char_check = _check_redir_chars;
		*is_double = _is_double_redir;
		*delims = "<>";
		break;
	}
}

char *_get_partition(char *copy, int *pos, int *sep, part kind)
{
	char *partition = NULL;
	char *delims;
	int (*char_check)(const char *, int);
	int (*is_double)(int);
	int p = 0;

	_setup_partitioner(kind, &char_check, &is_double, &delims);

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

char **tokenize(char *text, char *delims, int limit)
{
	char **tokens = malloc(sizeof(void *) * limit);
	char *tok;
	int i = 0;

	tok = strtok(text, delims);

	do {
		tokens[i] = tok;
		tok = strtok(NULL, delims);
	} while ((++i < limit) && (tok != NULL));

	tokens[i] = NULL;

	free(tok);
	return (tokens);
}

char *get_separation(const char *line, int *sep)
{
	static int pos = 0;
	static char *copy = NULL;
	char *separation;

	free(copy);
	copy = str_dup(&(line[pos]));

	separation = _get_partition(copy, &pos, sep, SEPAR);

	if (!separation)
	{
		free(copy);
		copy = NULL;
		pos = 0;
		/* *sep = -1; */
	}

	return (separation);
}

char *get_redirection(const char *line, int *redir)
{
	static int pos = 0;
	static char *copy = NULL;
	static int delay = -1;
	int hold;
	char *redirection;

	/* free previous string and create a new one from the  updated position */
	free(copy);
	copy = str_dup(&(line[pos]));

	/* get the next next token and update values */
	redirection = _get_partition(copy, &pos, redir, REDIR);

	if (!redirection)
	{
		/* last item extracted; reset values */
		free(copy);
		copy = NULL;
		pos = 0;
		delay = -1;
	}
	else
	{
		/* delay update of redir to next call */
		hold = *redir;
		*redir = delay;
		delay = hold;
	}

	return (redirection);
}

char *remove_comment(char *text, char *comment)
{
	/* line is a comment */
	for (int c = 0; comment[c] != '\0'; c++)
		if (comment[c] == text[0])
			return (NULL);

	/* extract non-comment slice*/
	text = str_dup(text);
	text = strtok(text, comment);
	return (text);
}
