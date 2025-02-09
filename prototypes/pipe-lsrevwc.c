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
	int pipe_a[2], pipe_b[2];
	char *ls_cmd[] = {"/usr/bin/ls", "-l", "../..", NULL};
	char *rev_cmd[] = {"/usr/bin/rev", NULL};
	char *wc_cmd[] = {"/usr/bin/wc", NULL};

	/*
	 * exercise 4: pipe ls to rev
	 *     simulate: 'ls | rev | wc'
	 *
	 * fork, execve, dup2, and pipe
	 *
	 * execve /bin/ls in a forked process
	 * execve /usr/bin/rev in another forked proc
	 *
	 * note: it's safer to close the write-end of a pipe
	 */

	/*
	 * note: because the returns of the function calls are not handled this
	 * code is unsafe. to implement it, be sure to add checks on all the
	 * appripriate return values
	 */

	/*
	 * make the program that receives data, the parent of
	 * the program that outputs data
	 */
	pipe(pipe_a);
	pipe(pipe_b);

	if (fork() == 0)
	{
		close(pipe_a[READ_END]);
		close(pipe_b[READ_END]);
		close(pipe_b[WRITE_END]);

		dup2(pipe_a[WRITE_END], STDOUT_FILENO);
		execve(ls_cmd[0], ls_cmd, NULL);
	}

	if (fork() == 0)
	{
		close(pipe_a[WRITE_END]);
		close(pipe_b[READ_END]);

		dup2(pipe_a[READ_END], STDIN_FILENO);
		dup2(pipe_b[WRITE_END], STDOUT_FILENO);
		execve(rev_cmd[0], rev_cmd, NULL);
	}

	if (fork() == 0)
	{
		close(pipe_a[READ_END]);
		close(pipe_a[WRITE_END]);
		close(pipe_b[WRITE_END]);

		dup2(pipe_b[READ_END], STDIN_FILENO);
		execve(wc_cmd[0], wc_cmd, NULL);
	}

	wait(NULL);
	exit(EXIT_SUCCESS);
}
