#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h> /* file mode_t defs */

/* create/open filename given and redirect stdout to it in append mode */

int main(int c, char **args)
{
	int fdesc;
	int hold_stdout;
	int fmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP; /* rw-rw---- */
	int fflags = O_CREAT | /*O_APPEND |*/ O_RDWR;

	if (c < 2)
		return (1);

	hold_stdout = dup(STDOUT_FILENO);

	fdesc = open(args[1], fflags, fmode);
	dup2(fdesc, STDOUT_FILENO);
	/* close(fdesc); */

	printf("file: output redirected to new file descriptor\n");
	printf("file: testing subsequent writes to stdout\n");


	dup2(hold_stdout, STDOUT_FILENO);
	/* close(hold_stdout); */

	printf("stdout: file descriptor closed\n");
	printf("stdout: output restored to stdout\n");



	return (0);
}
