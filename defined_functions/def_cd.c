#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "util_cd.h"
#include "util_env.h"

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

    if (chdir(path) != 0) /* attempt cd */
    {
        perror("cd");
        return (-1);
    }

    return (0);
}
