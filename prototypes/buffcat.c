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
 *                  /\_/\
 *                 ( o.o )
 *                  > ^ <
 *        ___ _____/     \_____ ___
 *      .'   `.-===-\   /-===-.`   '.
 *     /      .-"""""-.-"""""-.      \
 *    /'             =:=             '\
 *  .'  ' .:    o   -=:=-   o    :. '  `.
 *  (.'   /'. '-.....-'-.....-' .'\   '.)
 *  /' ._/   ".     --:--     ."   \_. /
 *  |  '|      ".  ---:---  ."     |'  |
 *  |   |       |  ---:---  |      |   |
 *   \  |        \____.____/       |  /
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
	int fdesc, len = 64;

	if (c < 2)
		return (EINVAL);

	fdesc = open(args[1], O_RDONLY);
	if (fdesc < 0)
		return (errno);

	readwrite(fdesc, STDOUT_FILENO, len);

	close(fdesc);

	return (0);
}
