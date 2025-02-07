#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define OUT_END 0
#define IN_END 1

extern char **environ;

int main(void)
{
	int pipefd[2];
	char *rev_cmd[] = {"/usr/bin/rev", NULL};
	char *ls_cmd[] = {"/usr/bin/ls", "-l", ".", NULL};

	/*
	 * exercise 4: pipe ls to rev
	 *     simulate: 'ls | rev'
	 *     fork, execve, dup2, and pipe
	 *
	 * execve /bin/ls in a forked process
	 * execve /usr/bin/rev in another forked proc
	 *
	 * consult man 2 pipe
	 * note: it's safer to close the write-end of a pipe
	 */

	/*
	 * make the program that receives data, the parent of
	 * the program that outputs data
	 */
	if (fork() == 0)
	{
		pipe(pipefd);

		if (fork() == 0)
		{
			close(pipefd[OUT_END]);
			dup2(pipefd[IN_END], STDOUT_FILENO);
			execve(ls_cmd[0], ls_cmd, NULL);
		}
		close(pipefd[IN_END]);
		dup2(pipefd[OUT_END], STDIN_FILENO); /* logic of this pisses me off */
		execve(rev_cmd[0], rev_cmd, NULL);
	}

	wait(NULL);
	exit(EXIT_SUCCESS);
}
