#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "util_str.h"
#include "util_path.h"
#include "util_env.h"

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
	int a = 0, b = 0;
	char *concat;
	char *tail;

	while (dirname[a] != '\0')
		a++;
	while (filename[b] != '\0')
		b++;

	concat = malloc(sizeof(concat) * (a + b + 1));
	str_paste(&concat, dirname);

	tail = &concat[a];
	str_paste(&tail, "/");

	tail = &concat[a + 1];
	str_paste(&tail, filename);

	return (concat);
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

char *_which(char *basename)
{
	char **paths, *fullpath, *pathenv, *mailback = NULL;
	int p = 0;

	pathenv = _getenv("PATH");
	pathenv = _strdup(pathenv);
	paths = tokenize(pathenv, "=:", 64);

	while (paths[p] != NULL)
	{
		fullpath = build_fullpath(paths[p], basename);
		if (verify_fullpath(fullpath))
		{
			mailback = fullpath;
			break;
		}
		free(fullpath);
		p++;
	}

	free(paths);
	free(pathenv);
	return (mailback);
}
