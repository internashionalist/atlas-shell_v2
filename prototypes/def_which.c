#include <stdlib.h>
#include <stdio.h>
#include "util_str.h"
#include "util_path.h"
#include "util_env.h"

char *_which(char *basename)
{
	char **paths, *fullpath, *pathenv, *mailback = NULL;
	int p = 0;


	if (is_pathed(basename))
		return (str_dup(basename));

	pathenv = _getenv("PATH");
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
