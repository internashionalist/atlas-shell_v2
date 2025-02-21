#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dec_cd.h"
#include "dec_env.h"
#include "dec_str.h"
#include "dec_exit.h"


int is_builtin(char *cmd)
{
    if (!cmd)
        return 0;
    if (_strcmp(cmd, "echo") == 0)
        return 1;
    if (_strcmp(cmd, "env") == 0)
        return 1;
    if (_strcmp(cmd, "cd") == 0)
        return 1;
    if (_strcmp(cmd, "exit") == 0)
        return 1;
    return 0;
}

int handle_builtin(char **input_tokens)
{
    if (_strcmp(input_tokens[0], "exit") == 0)
    {
        exit_shell(input_tokens);
        return (1);
    }
    else if (_strcmp(input_tokens[0], "cd") == 0)
    {
        change_dir(input_tokens);
        return (1);
    }
    else if (_strcmp(input_tokens[0], "env") == 0)
    {
        print_env();
        return (1);
    }
    return (0);  /* built-in handled */
}
