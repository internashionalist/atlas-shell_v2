#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "_util_str.h"


int main(void)
{
	char *input_buf = NULL;
	size_t input_len = 0;

	do {
		if (input_buf != NULL)
		{
			if (!_strcmp(input_buf, "exit\n"))
				break;
			printf("%s", input_buf);
		}
		printf("$ ");
	} while (getline(&input_buf, &input_len, stdin));

	free(input_buf);
	return (0);
}
