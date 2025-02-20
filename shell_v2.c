#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "dec_cmd.h"
#include "dec_env.h"
#include "dec_parser.h"
#include "dec_path.h"
#include "dec_str.h"

void print_prompt(char *prompt)
{
	if (!prompt)
		prompt = "$ ";
	if (isatty(STDIN_FILENO))
		printf("%s", prompt);
}

int main(int c, char **args)
{
	char *inputline = NULL;
	size_t input_len = 0;

	init_env();

	if (c > 1)
	{
		inputline = deserialize(&(args[1]));
		proc_cmds(inputline);
	}
	else
	{
		print_prompt(NULL);
		while (getline(&inputline, &input_len, stdin) > -1)
		{
			if (str_match(inputline, "exit\n"))
				break;
			else
				proc_cmds(inputline);
			print_prompt(NULL);
		}
	}

	reset_env();

	free(inputline);

	return (0);
}
