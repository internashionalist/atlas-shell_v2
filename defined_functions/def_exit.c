#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "util_exit.h"
#include "util_str.h"

/**
 * exit_shell - exits the shell
 * @input_tokens: array of input tokens
 *
 * Return: void
 */
void exit_shell(char **input_tokens)
{
    int status = 0;

    if (input_tokens[1])
        status = _atoi(input_tokens[1]) % 256;
    
    if (input_tokens)
        free(input_tokens);

    exit(status);
}
