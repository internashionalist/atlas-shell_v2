#include <stdio.h>
#include <unistd.h>

/* this will duplicate the calling process (bash) */

int main(void)
{
	pid_t my_pid, fork_pid;

	printf("before fork:\n");

	fork_pid = fork();
	my_pid = getpid();

	printf("after fork:\n");

	switch (fork_pid) {
		case -1:
			perror("fork failure:\n");
			return (1);
		case 0:
			printf("child pid: %d\n", my_pid);
			break;
		default:
			printf("parent pid: %d\n", my_pid);
			break;
	}

	return (0);
}
