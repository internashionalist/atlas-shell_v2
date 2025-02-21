#include "dec_str.h"
#include "dec_path.h"
#include "dec_env.h"
#include "dec_parser.h"
#include <stdio.h>
#include <stdlib.h>

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

int verify_fullpath(char *fullpath)
{
	struct stat st;

	if (!stat(fullpath, &st))
		return (1);
	else
		return (0);
}

char *build_fullpath(char *dirname, char *filename)
{
	char *dir_slash_file, *dir_slash;

	dir_slash = str_dupcat(dirname, "/");
	dir_slash_file = str_dupcat(dir_slash, filename);
	free(dir_slash);

	return (dir_slash_file);
}

char *_which(char *basename)
{
	char **paths, *fullpath, *pathenv, *mailback = NULL;
	int p = 0;

	if (is_pathed(basename))
		return (str_dup(basename));

	pathenv = _getenv("PATH");
	if (!pathenv)
		return (NULL);

	pathenv = str_dup(pathenv);
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
