#include "chepe-str.h"
#include "env-utils.h"
#include <stdio.h>
#include <stdlib.h>

int _getenvid(const char *name)
{
	int len = 0, index = 0;
	char *name_eq;

	name_eq = str_concat((char *) name, "=");

	while (name_eq[len] != '\0')
		len++;

	while (environ[index] != NULL)
	{
		if (str_nmatch(name_eq, environ[index], len))
		{
			free(name_eq);
			return(index);
		}
		index++;
	}

	free(name_eq);
	return (-1);
}

char *_getenvp(const char *name)
{
	int index;
	char *envp = NULL;

	index = _getenvid(name);

	if (index > -1)
		envp = environ[index];

	return (envp);
}

char *_getenv(const char *name)
{
	char *value = _getenvp(name);
	int c = 0;

	if (value)
	{
		while (value[c] != '=')
			c++;
		value = &(value[++c]);
	}

	return (value);
}

int _unsetenv(const char *name)
{
	int last = 0;
	int index = _getenvid(name);

	while (environ[last] != NULL)
		last++;
	last--;

	if (index > -1)
	{
		environ[index] = environ[last];
		environ[last] = NULL;
	}

	return (0);
}

/* int _setenv(const char *name, const char *value, int overwrite) */
/* { */
/* 	char *envp = _getenvp(name); */
/* 	int c = 0; */

/* 	if (!envp) */
/* 		return (-1); */
/* 	else */
/* 		return (c); */

/* 	return (0); */
/* } */

