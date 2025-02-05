#include "util_env.h"
#include <stdio.h>
#include <stdlib.h>

int main(int c, char **argv)
{
	(void) c;
	(void) argv;

	if ( c < 3)
		return(1);

	init_env();
	print_env();
	_setenv(argv[1], argv[2], 1);
	_setenv("FOO", "bar", 1);
	_setenv("LANGUAGE", "fr", 1);
	_setenv("LANG", "C", 1);
	print_env();
	reset_env();

	return (0);
}
