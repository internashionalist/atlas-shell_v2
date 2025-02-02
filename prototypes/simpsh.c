#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char **tokenize(char *inputline)
{
	int max_tokens = 2024;
	char *delims = " \n";
	char **tokens = malloc(sizeof(void *) * max_tokens);
	char *tok = strtok(inputline, delims);

	int i = 0;
	do {
		tokens[i] = tok;
		tok = strtok(NULL, delims);
	} while ((++i < max_tokens) && (tok != NULL));

	tokens[i] = NULL;

	free(tok);
	return (tokens);
}

int process_input(char **strings)
{
	int wstatus;

	switch (fork())
	{
		case -1:
			return (-1);
		case 0:
			if (execve(strings[0], strings, NULL) == -1)
				return (-1);
			break;
		default:
			wait(&wstatus);
	}
	return (wstatus);
}

int main(void)
{
	char *inputline = NULL;
	char **input_tokens = NULL;
	size_t input_len = 0;

	while (1)
	{
		printf("$ ");

		if (getline(&inputline, &input_len, stdin) == -1)
			continue;
		if (!strcmp(inputline, "exit\n"))
			break;
		else
		{
			input_tokens = tokenize(inputline);
			process_input(input_tokens);
			free(input_tokens);
		}
	}

	free(inputline);

	return (0);
}
