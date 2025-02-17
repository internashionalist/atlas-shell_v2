#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "util_exit.h"
#include "util_str.h"

/*
 * str_numeric - checks if a string is a valid integer
 * @s: string to check.
 *
 * Return: 1 if the string is numeric, otherwise 0
 */
static int str_numeric(const char *s)
{
	int i = 0;
	int c; /* character */

	if (s[i] == '-' || s[i] == '+') /* skip sign */
		i++;

	if (s[i] == '\0') /* empty string */
		return (0);

	while (s[i] != '\0')
	{
		c = s[i]; /* get first char */
		if (c < '0' || c > '9') /* check if numeric */
			return (0);
		i++;
	}

	return (1);
}

/**
 * exit_shell - exits the shell with a status
 * @input_tokens:   array of input tokens
 *                  input_tokens[0] - "exit"
 *                  input_tokens[1] - status
 * Return: void
 */
void exit_shell(char **input_tokens)
{
    int status = 0;

    if (input_tokens[1])
    {
        if (!str_numeric(input_tokens[1])) /* if not numeric */
        {
            fprintf(stderr, "exit: %s: numeric argument required\n",
                input_tokens[1]);
            return;
        }

        status = _atoi(input_tokens[1]); /* convert to integer */
        status = (status % 256 + 256) % 256; /* limit to 0-255 */
    }

    free(input_tokens); /* free array */

    exit(status);
}
