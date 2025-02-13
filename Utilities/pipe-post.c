#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

extern char **environ;

int main()
{
	int post_pipe[2];
	char *text;
	char *rev_cmd[] = {"/usr/bin/rev", NULL};

	pipe(post_pipe);

	if (fork() == 0)
	{
		close(post_pipe[READ_END]);

		dup2(post_pipe[WRITE_END], STDOUT_FILENO);
		execve(rev_cmd[0], rev_cmd, environ);
	}

	text = malloc(sizeof(char) * 32);
	read(post_pipe[READ_END], text, 32);
	write(STDOUT_FILENO, text, 32);

	close(post_pipe[WRITE_END]);
	close(post_pipe[READ_END]);

	wait(NULL);
	exit(EXIT_SUCCESS);
}
