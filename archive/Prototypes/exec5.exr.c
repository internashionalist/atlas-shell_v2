#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char *cmddef[] = {"/usr/bin/ls", ".", NULL};
	pid_t fork_pid;
	int wstatus;

	for (int i = 0; i < 5; i++)
	{
		fork_pid = fork();
		switch (fork_pid)
		{
			case -1:
				perror("fork failure:\n");
				return (1);
			case 0:
				if (execve(cmddef[0], cmddef, NULL) == -1)
					perror("no execve: ");
				continue;
			default:
				wait(&wstatus);
		}
	}

	return (0);
}
