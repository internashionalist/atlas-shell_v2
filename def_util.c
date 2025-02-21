#include "dec_path.h"
#include "dec_util.h"
#include "dec_parser.h"
#include "dec_str.h"
#include "dec_env.h"
#include <stdio.h>
#include <stdlib.h>


int analyze_paths(char **paths, char *filename)
{
	struct stat st;
	char *fullpath;
	int err = -1;

	for (int p = 1; paths[p] != NULL; p++)
	{
		fullpath = build_fullpath(paths[p], filename);
		if (print_fullpath(fullpath, &st) < 0)
		{
			free(fullpath);
			err = -1;
		}
		else
		{
			free(fullpath);
			err = 0;
			break;
		}
	}

	return (err);
}


void print_paths()
{
	char *path = navigate_path();

	while (path)
	{
		printf("%s\n", path);
		path = navigate_path();
	}
}


int print_fullpath(char *fullpath, struct stat *st)
{
	if (stat(fullpath, st) == 0)
	{
		printf("%s\n", fullpath);
		return (0);
	}
	else
		return (-1);
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

void print_env()
{
	int i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

char *read_line(char *text)
{
	static char **lines;
	static char *buffer = NULL;
	static int l = 0;
	char *line = NULL;

	if (text)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		if (lines)
		{
			free(lines);
			lines = NULL;
		}

		buffer = str_dup(text);
		lines = tokenize(buffer, "\n", 2048);
		l = 0;
	}

	if (lines && lines[l])
	{
		line = lines[l];
		l++;
		return (line);
	}
	else
	{
		l = 0;
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		if (lines)
		{
			free(lines);
			lines = NULL;
		}
		l = 0;

		return (NULL);
	}
}
