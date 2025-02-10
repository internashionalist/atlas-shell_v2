#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END  1

extern char **environ;

int main(void)
{
	int pipe_a[2];
	char *ls_cmd[] = {"/usr/bin/ls", NULL};
	char *rev_cmd[] = {"/usr/bin/rev", NULL};

	pipe(pipe_a);

	if (fork() == 0)
	{
		close(pipe_a[READ_END]);

		dup2(pipe_a[WRITE_END], STDOUT_FILENO);
		execve(ls_cmd[0], ls_cmd, NULL);
	}

	close(pipe_a[WRITE_END]);

	if (fork() == 0)
	{
		dup2(pipe_a[READ_END], STDIN_FILENO);
		execve(rev_cmd[0], rev_cmd, NULL);
	}

	close(pipe_a[READ_END]);
	wait(NULL);

	exit(EXIT_SUCCESS);
}
