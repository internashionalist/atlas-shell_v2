#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h> /* file mode_t defs */

/*
 * open/create filename, redirect stdout to it in overwrite mode
 */

int main(int c, char **args)
{
	int fdesc;
	int fmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP; /* rw-rw---- */


	if (c < 2)
		return (EINVAL);

	fdesc = open(args[1], O_CREAT | O_RDWR, fmode);

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
