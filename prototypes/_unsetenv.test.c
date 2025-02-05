#include "util_env.h"
#include <stdio.h>
#include <stdlib.h>

int main(int c, char **argv)
{
	char *value;

	if (c < 2)
		return (1);
	else
	{
		_print_env();
		for (int i = 1; i < c; i++)
		{
			value = _getenv(argv[i]);
			printf("%s :\n\t%s\n", argv[i], value);

			_unsetenv(argv[i]);

			value = _getenv(argv[i]);
			printf("\t%s\n", value);
		}
		_print_env();
	}

	return (0);
}
