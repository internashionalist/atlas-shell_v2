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
	int pre_pipe[2];
	char *text;
	char *rev_cmd[] = {"/usr/bin/rev", NULL};

	pipe(pre_pipe);

	text = malloc(sizeof(char) * 32);
	read(STDIN_FILENO, text, 32);
	write(pre_pipe[WRITE_END], text, 32);

	if (fork() == 0)
	{
		close(pre_pipe[WRITE_END]);

		dup2(pre_pipe[READ_END], STDIN_FILENO);
		execve(rev_cmd[0], rev_cmd, environ);
	}

	close(pre_pipe[WRITE_END]);
	close(pre_pipe[READ_END]);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
