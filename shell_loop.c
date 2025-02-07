#include "shell.h"
#include "str_helpers.h"

/**
 * shell_loop - prompt, read, parse, execute
 * @info: pointer to shell state info
 *
 * Return: 0 on success
 */
int shell_loop(info_t *info)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t num_read; /* chars read */
	char *token;
	char **args;
	int num_tokens;
    int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO)) /* if interactive */
			prompt();

		num_read = getline(&line, &len, stdin); /* is this right?? */
		if (num_read == -1) /* EOF or error */
		{
			if (line)
				free(line);
			break;
		}
		info->line_number++;

		if (num_read > 0 && line[num_read - 1] == '\n') /* remove newline if found */
			line[nread - 1] = '\0';

		if (_strcmp(line, "exit") == 0)
			break;

		num_tokens = tokenize_input(line, &tokens);
        if (num_tokens == -1 || num_tokens == 0)
        {
            free(line);
            continue;
        }

        status = execute(tokens, info);
    
        for (int i = 0; i < num_tokens; i++)
            free(tokens[i]);
        free(tokens);
        tokens = NULL;
    }

    free(line);
    return (status);
}
