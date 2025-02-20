#include "util_env.h"
#include <stdio.h>
#include <stdlib.h>

int main(int c, char **argv)
{
	char *value;

	if (c < 2)
		return (1);
	else
		for (int i = 1; i < c; i++)
		{
			value = _getenv(argv[i]);
			printf("%s:\n\t_getenv: %s\n", argv[i], value);
		}
	return (0);
}
