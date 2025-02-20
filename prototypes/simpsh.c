#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "util_str.h"
#include "util_which.h"
#include "util_env.h"

int run_cmd(char *inputline)
{
	int wstatus;
	char *fullpath, **input_tokens = NULL;

	input_tokens = tokenize(inputline, " \n", 1024);

	fullpath = _which(input_tokens[0]);

	if (!fullpath)
	{
		free(fullpath);
		fullpath = NULL;
		return(-1);
	}
	else
	{
		input_tokens[0] = fullpath;
	}

	switch (fork())
	{
		case -1:
			return (-1);
		case 0:
			if (execve(input_tokens[0], input_tokens, environ) == -1)
				return (-1);
			break;
		default:
			wait(&wstatus);
	}

	free(fullpath);
	free(input_tokens);
	return (wstatus);
}

int main(void)
{
	char *inputline = NULL;
	size_t input_len = 0;

	init_env();

	while (1)
	{
		printf("$ ");

		if (getline(&inputline, &input_len, stdin) == -1)
			continue;

		if (!strcmp(inputline, "exit\n"))
			break;
		else
			run_cmd(inputline);
	}

	reset_env();

	free(inputline);

	return (0);
}
