#include "env-utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int c, char **argv)
{
	char *value, *test;

	if (c < 2)
		return (1);
	else
		for (int i = 1; i < c; i++)
		{
			value = _getenv(argv[i]);
			test = getenv(argv[i]);
			printf("%s :\n\t_getenv: %s\n", argv[i], value);
			printf("\n\tgetenv:  %s\n", test);
		}
	return (0);
}
