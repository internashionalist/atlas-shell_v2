#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t parent = getppid();

	printf("%u\n", parent);
	return (0);
}
