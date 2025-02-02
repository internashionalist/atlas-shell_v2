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

void print_str_array(char **strings)
{
	for (int i = 0; strings[i] != NULL; i++)
		printf("%d: %s\n", i, strings[i]);
}

int main(void)
{
	/*
	 * fork, execve, wait
	 *    pid checks
	 */

	char *inputline = NULL;
	char **input_tokens = NULL;
	size_t input_len = 0;

	while (1)
	{
		printf("$ ");

		if (getline(&inputline, &input_len, stdin) == -1);
			continue;

		if (!strcmp(inputline, "exit\n"))
			break;
		else
		{
			input_tokens = tokenize(inputline);
			print_str_array(input_tokens);
			free(input_tokens);
		}

	}

	free(inputline);

	return (0);
}
