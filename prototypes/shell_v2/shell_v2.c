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
			proc_cmds(inputline);
	}

	reset_env();

	free(inputline);

	return (0);
}
