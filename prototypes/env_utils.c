#include "chepe-str.h"
#include "env-utils.h"
#include <stdio.h>

char *_getenv(const char *name)
{
	int len = 0;
	char *value = NULL;

	while (name[len] != '\0')
		len++;

	for (int v = 0; environ[v] != NULL; v++)
		if (str_nmatch(name, environ[v], len))
			value = environ[v];
	if (value)
	{
		int c = 0;

		while (value[c] != '=')
			c++;

		value = &(value[++c]);
	}

	return (value);
}

/* int _setenv(const char *name, const char *value, int overwrite) */
/* { */
/* 	char *found = _getenv(name); */

/* 	if (!found) */
/* 		return (-1); */
/* 	else */

/* 	return (0); */
/* } */

/* char *_unsetenv( const char *name); */
