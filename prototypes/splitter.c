#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tokens(char *inputline)
{
	char *token = strtok(inputline, " ");

	do {
		printf("%s\n", token);
		token = strtok(NULL, " \n");
	} while (token != NULL);

	free(token);
}

int main(void)
{
	char *input_buf = NULL;
	size_t input_len = 0;

	do {
		if (input_buf != NULL)
		{
			if (!strcmp(input_buf, "exit\n"))
				break;
			else
				print_tokens(input_buf);
		}
		printf("$ ");
	} while (getline(&input_buf, &input_len, stdin));

	free(input_buf);
	return (0);
}
