#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1

extern char **environ;

void foward_msg(int head[2], int tail[2], int len)
{
	char *text = malloc(sizeof(char) * len);

	read(head[READ_END], text, len);
	write(tail[WRITE_END], text, len);

	free(text);
}

/*
 * usage:
 * echo some_text | ./endtoend
 */

int main()
{
	char *hello = "HELLO WORLD!!!!\n";
	int std_input[2] = {STDIN_FILENO, -1};
	int std_output[2] = {-1, STDOUT_FILENO};
	int inpipe[2], outpipe[2], len = 64;

	pipe(inpipe);
	pipe(outpipe);

	write(inpipe[WRITE_END], hello, 17);

	foward_msg(std_input, inpipe, len);
	foward_msg(inpipe, outpipe, len);
	foward_msg(outpipe, std_output, len);

	close(inpipe[READ_END]);
	close(inpipe[WRITE_END]);
	close(outpipe[READ_END]);
	close(outpipe[WRITE_END]);

	exit(EXIT_SUCCESS);
}
