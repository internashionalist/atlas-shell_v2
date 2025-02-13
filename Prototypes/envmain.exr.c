#include <stdio.h>

int main(int c, char **args, char **env)
{
	(void) c;
	(void) args;

	for (int i = 0; env[i] != NULL; i++)
		printf("%s\n", env[i]);
	return (0);
}
