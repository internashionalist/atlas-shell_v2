#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int count, char **argv)
{
	struct stat st;

	if (count < 2)
	{
		printf("insufficient parameters passed\n");
		return (1);
	}

	for (int i = 1; argv[i] != NULL; i++)
	{
		printf("%s: ", argv[i]);
		if (stat(argv[i], &st) == 0)
			printf("file confirmed.\n");
		else
			printf("file not found.\n");
	}

	return (0);
}
