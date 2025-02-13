#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "util_cd.h"
#include "util_env.h"

int change_dir(char **tokens)
{
    char *path = tokens[1];

    if (!path)
    {
        path = _getenv("HOME");
        if (!path)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return (-1);
        }
    }

    if (chdir(path) != 0)
    {
        perror("cd");
        return (-1);
    }

    return (0);
}
