/*
 * test the address of **env vs that of extern char **environ
 * write a func that prints each dir in the PATH env var
 * write a func that builds a linked list of PATH dirs
 */

char *_getenv(         /* man getenv(3) */
	const char *name);

int _setenv(           /* man setenv(3) */
	const char *name,
	const char *value,
	int overwrite);

char *_unsetenv(       /* man unsetenv(3) */
	const char *name);
