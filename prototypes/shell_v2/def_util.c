#include "dec_path.h"
#include "dec_util.h"
#include <stdio.h>
#include <stdlib.h>

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

void print_paths()
{
	char *path = navigate_path();

	do {
		printf("%s\n", path);
		path = navigate_path();
	} while (path);
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


