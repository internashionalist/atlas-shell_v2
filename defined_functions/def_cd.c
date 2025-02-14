#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "util_cd.h"
#include "util_env.h"
#include "_util_str.h"

int change_dir(char **tokens)
{
    char *path = tokens[1]; /* get path from tokens */

    if (!path) /* if no path given, go HOME */
    {
        char *home = _getenv("HOME");
        if (!home)
        {
            return (0);
        }

        path = home;
    }
    else if (path && _strcmp(path, "-") == 0) /* if path is "-" */
    {
        char *oldpwd = _getenv("OLDPWD");
        if (!oldpwd)
        {
            char cwd[PATH_MAX]; /* current working directory buffer */
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
            return 0;
        }
        path = oldpwd; /* otherwise, move on */
    }
    if (chdir(path) != 0) /* attempt cd */
    {
        fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", path);
        return (-1);
    }

    if (tokens[1] && _strcmp(tokens[1], "-") == 0)
    {
        char cwd[PATH_MAX]; /* current working directory buffer */
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n", cwd); /* prove it's still the same CWD */
    }

    return (0);
}
