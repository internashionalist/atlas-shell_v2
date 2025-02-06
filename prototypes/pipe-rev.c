#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

int main()
{
	int pipefd[2];
	pid_t parent;
	char *rev_cmd[] = {"/usr/bin/rev", NULL};

	/*
	 * exercise 3: pipe stdout to /usr/bin/rev
	 * usage:
	 *     echo "text" | rev.exec
	 *
	 * create pipe
	 *     redir stdout to the write-end
	 *     redir the read-end to the input of rev
	 */

	if (pipe(pipefd) < 0)
		exit(EPIPE);

	parent = fork();
	if (parent < 0)
		exit(EBADFD);

	if (!parent)
	{
		close(pipefd[READ_END]);
		dup2(STDOUT_FILENO, pipefd[WRITE_END]);
		wait(NULL);
		close(pipefd[WRITE_END]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[WRITE_END]);
		dup2(STDIN_FILENO, pipefd[READ_END]);
		if (execve(rev_cmd[0], rev_cmd, NULL) < 0)
			perror("no execve: ");
		_exit(errno);
	}
}
