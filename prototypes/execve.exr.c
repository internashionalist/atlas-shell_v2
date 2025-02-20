#include <stdio.h>
#include <unistd.h>

int main(int count, char *argv[])
{
	if (count == 1)
		printf("please specify a program and arguments\n");
	else
		if (execve(argv[1], &argv[1], NULL) == -1)
			perror("no execve: ");

	return (0);
}
