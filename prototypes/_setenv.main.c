#include "env-utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int c, char **argv)
{
	(void) c;
	(void) argv;

	if ( c < 3)
		return(1);

	stash_env(environ);
	_setenv(argv[1], argv[2], 1);
	_print_env();
	/* reset_env(); */

	return (0);
}
