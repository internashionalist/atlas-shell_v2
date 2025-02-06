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

	/*
	 * create pipe
	 *
	 * use dup2 to
	 *     redirect the output of the first command
	 *     into the write end of the pipe
	 *
	 *     redirect the read end of the pipe
	 *     into the input of the second command
	 */

	/*
	 * exercise 4: command to command
	 *
	 * simulate ls | rev
	 *
	 * use fork, execve, dup2, and pipe
	 *
	 * execve /bin/ls in a forked process
	 * execve /usr/bin/rev in another forked proc
	 *
	 * pipe ls to rev
	 *
	 * consult man 2 pipe
	 * note: it's safer to close the write-end of a pipe
	 */

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
