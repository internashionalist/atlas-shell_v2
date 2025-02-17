#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "defined_functions/util_str.h"
#include "defined_functions/util_which.h"
#include "defined_functions/util_env.h"
#include "defined_functions/util_cd.h"
#include "defined_functions/util_exit.h"

int process_cmd(char **input_tokens)
{
	int wstatus;
	char *command = input_tokens[0];
	char *fullpath = NULL;

	if (command[0] == '.' || command[0] == '/') /* absolute PATH */
	{
		if (access(command, X_OK) == 0) /* check if executable */
			fullpath = str_dup(command);
		else
			return (-1);
	}
	else
	{
		fullpath = _which(command); /* search PATH */
		if (!fullpath)
			return (-1);
	}

	input_tokens[0] = fullpath; /* replace command with complete PATH */

	pid_t pid = fork(); /* fork to create child process */
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0) /* child process */
	{
		if (execve(input_tokens[0], input_tokens, environ) == -1) /* execute */
		{
			perror("execve");
			exit(127);
		}
	}
	else
	{
		wait(&wstatus); /* wait for child process to finish */
	}

	free(fullpath); /* free allocated memory in parent process */
	return (wstatus);
}


int main(void)
{
	char *inputline = NULL;
	char **input_tokens = NULL;
	size_t input_len = 0;
	ssize_t n_read;

	init_env();

	while (1)
	{
		if (isatty(STDIN_FILENO)) /* if interactive mode */
			printf("$ ");

		n_read = getline(&inputline, &input_len, stdin); /* read input */
		if (n_read == -1) /* EOF or error */
			break;

		if (n_read > 0 && inputline[n_read - 1] == '\n') /* remove \n */
			inputline[n_read - 1] = '\0';

		input_tokens = tokenize(inputline, " \t", 1024); /* tokenize */
		if (!input_tokens || !input_tokens[0]) /* if empty input */
		{
			free(input_tokens);
			continue;
		}

		if (_strcmp(input_tokens[0], "exit") == 0) /* exit built-in */
		{
			exit_shell(input_tokens);
		}
		else if (_strcmp(input_tokens[0], "cd") == 0) /* cd built-in */
		{
			change_dir(input_tokens);
		}
		else if (_strcmp(input_tokens[0], "env") == 0) /* env built-in */
		{
			print_env();
		}
		else
		{
			char *cmd_cpy = str_dup(input_tokens[0]); /* copy before procs */
			int status = process_cmd(input_tokens); /* process command */
			if (status == -1)
				printf("Command not found: %s\n", input_tokens[0]);
			free(cmd_cpy);
		}

		free(input_tokens);
	}

	reset_env();

	free(inputline);

	return (0);
}
