#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h> /* file mode_t defs */


int main(int c, char **args)
{
	int fdesc;
	int fmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP; /* rw-rw---- */
	int fflags = O_CREAT | O_APPEND | O_WRONLY;

	if (c < 2)
		return (EINVAL);

	fdesc = open(args[1], fflags, fmode);

	if (fdesc < 0)
		return (errno);

	if (dup2(fdesc, STDOUT_FILENO) < 0)
		return(errno);

	printf("if successful, a new file with this should've been created\n");
	printf("testing what happens in subsequent calls to stdout\n");
	printf("testing...\n");

	close(fdesc);

	return (0);
}
