#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t my_pid, fork_pid;
	int wstatus;

	fork_pid = fork();
	my_pid = getpid();

	switch (fork_pid) {
		case -1:
			perror("fork failure:\n");
			return (1);
		case 0:
			printf("child pid: %d\n", my_pid);
			break;
		default:
			wait(&wstatus);
			printf("wait status: %d\n", wstatus);
			printf("parent pid: %d\n", my_pid);
			break;
	}

	return (0);
}
