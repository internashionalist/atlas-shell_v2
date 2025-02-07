#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <wait.h>
#include <sys/stat.h> /* file mode_t defs */

int main(int c, char **args)
{
	int fdesc, fork_pid, wstatus;
	int fmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP; /* rw-rw---- */
	int fflags = O_CREAT | O_APPEND | O_WRONLY;

	if (c < 2)
		return (EINVAL);

	fdesc = open(args[1], fflags, fmode);

	if (fdesc < 0)
		return (errno);

	char *cmd[] = {"/usr/bin/rev", args[1], NULL};

	fork_pid = fork();
	switch (fork_pid)
	{
		case -1:
			perror("fork failure: ");
			return (1);
		case 0:
			if (execve(cmd[0], cmd, NULL) == -1)
				perror("execve failure: ");
			break;
		default:
			wait(&wstatus);
	}

	close(fdesc);

	return (0);
}
