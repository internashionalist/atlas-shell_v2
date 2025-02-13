#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

int main(int c, char **args)
{
	int pipefd[2];
	pid_t parent;
	char buf;

	if (c < 2)
		exit(EINVAL);
	if (pipe(pipefd) < 0)
		exit(EPIPE);

	parent = fork();
	if (parent < 0)
		exit(EBADFD);
	if (!parent)
	{
		close(pipefd[READ_END]);
		write(pipefd[WRITE_END], args[1], strlen(args[1]));
		close(pipefd[WRITE_END]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[WRITE_END]);
		while(read(pipefd[READ_END], &buf, 1) > 0 )
			write(STDOUT_FILENO,&buf, 1);
		write(STDOUT_FILENO,"\n", 1);
		close(pipefd[READ_END]);
		_exit(EXIT_SUCCESS);
	}
}
