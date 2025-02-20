#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <wait.h>
#include <signal.h>
#include <sys/stat.h> /* file mode_t defs */

#define READ_END  0
#define WRITE_END 1

/*
 * read filename contents and redirect them to subproc's stdin
 */

void readwrite(int readin, int writeout, int len)
{
	char *buffer = malloc(sizeof(char) * len);
	int rlen = 0;

	do {
		rlen = read(readin, buffer, len);
		write(writeout, buffer, rlen);
	} while (rlen > 0);

	free(buffer);
}

int main(int c, char **args)
{
	char *cmd[] = {"/usr/bin/rev", NULL};
	int fdesc, subproc, wstatus, pipefd[2], len = 64;

	if (c < 2)
		return (EINVAL);

	fdesc = open(args[1], O_RDONLY | O_ASYNC);
	if (fdesc < 0)
		return (errno);

	pipe(pipefd);

	subproc = fork();
	switch (subproc)
	{
		case -1:
			perror("fork failure: ");
			return (1);
		case 0:
			close(pipefd[WRITE_END]);
			dup2(pipefd[READ_END], STDIN_FILENO);
			if (execve(cmd[0], cmd, NULL) == -1)
				perror("execve failure: ");
			break;
		default:
			close(pipefd[READ_END]);
			/* dup2(pipefd[WRITE_END], STDOUT_FILENO); */
			/* readwrite(fdesc, STDOUT_FILENO, len); */
			readwrite(fdesc, pipefd[WRITE_END], len);
			close(fdesc);
			close(pipefd[WRITE_END]);
			wait(&wstatus);
	}

	return (0);
}
