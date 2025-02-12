#include "util_str.h"
#include "util_path.h"
#include "util_env.h"
#include <stdio.h>
#include <stdlib.h>

/******** BASIC PATH HANDLING ********/

int is_pathed(char *cmdpath)
{
	switch (cmdpath[0])
	{
		case '.':
			return 1;
		case '/':
			return 1;
		default:
			return 0;
	}
}


char *navigate_path()
{
	static int p = 0;
	static char *pathvar = NULL;
	static char **paths = NULL;

	if (!p)
	{
		/*
		 * strtok destroys the original string and thus, without making a
		 * duplicate, subsequent calls are impossible
		 */
		pathvar = _getenv("PATH");
		pathvar = str_dup(pathvar);
		paths = tokenize(pathvar, "=:", 64);
	}

	p++;
	if (paths[p] != NULL)
		return (paths[p]);
	else
	{
		free(paths);
		free(pathvar);
		pathvar = NULL;
		paths = NULL;
		p = 0;
		return NULL;
	}
}

void print_paths()
{
	char *path = navigate_path();

	do {
		printf("%s\n", path);
		path = navigate_path();
	} while (path);
}

int verify_fullpath(char *fullpath)
{
	struct stat st;

	if (!stat(fullpath, &st))
		return (1);
	else
		return (0);
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

char *build_fullpath(char *dirname, char *filename)
{
	char *dir_slash_file, *dir_slash;

	dir_slash = str_concat(dirname, "/");
	dir_slash_file = str_concat(dir_slash, filename);
	free(dir_slash);

	return (dir_slash_file);
}

int analyze_paths(char **paths, char *filename)
{
	struct stat st;
	char *fullpath;
	int err = 0;

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
