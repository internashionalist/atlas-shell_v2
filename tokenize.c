#include "shell.h"

/**
 * tokenize_input - splits input string into tokens
 * @input: input string
 * @tokens: array of split input tokens
 *
 * Return: number of tokens created or -1 on error
 */
int tokenize_input(char *input, char ***tokens)
{
	char *token;
	int token_counter = 0;
	int i; /* for freeing tokens */

	*tokens = malloc(TOK_SIZE * sizeof(char *));
	if (*tokens == NULL)
		return (-1);
	token = _strtok(input, DELIM); /* _strtok ? also need to define DELIM in .h */
	while (token != NULL)
	{
		(*tokens)[token_counter] = _strdup(token); /* _strdup ? */
		if ((*tokens)[token_counter] == NULL)
		{
			for (i = 0; i < token_counter; i++)
				free((*tokens)[i]);
			free(*tokens);
			return (-1);
		}
		token_counter++;
		token = strtok(NULL, DELIM);
	}
	(*tokens)[token_counter] = NULL;
	return (token_counter);
	}
