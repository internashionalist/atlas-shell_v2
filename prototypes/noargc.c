#include <stdio.h>

int main(int count, char *arg_strings[])
{
	(void) count;

	for (int i = 0; arg_strings[i] != NULL; i++)
		printf("%s\n", arg_strings[i]);

	return (0);
}
