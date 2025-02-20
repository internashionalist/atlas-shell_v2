#include <stdio.h>
#include <stdlib.h>
#include "util_str.h"
#include "util_env.h"

static char **local_env = NULL;

/******** INTERNAL ********/

char *compose_varval(char *var, char *val)
{
	char *var_eq = str_concat(var, "=");
	char *varval = str_concat(var_eq, val);

	free(var_eq);
	return (varval);
}

int env_length(void)
{
	int len = 0;

	len = 0;
	while (environ[len] != NULL)
		len++;

	return (len);
}

char **stash_env(char **env)
{
	static char **stash = NULL;

	if (env)
		stash = env;

	return stash;
}

char **extend_env(char **env, int add)
{
	int len = 0;
	char **new_env = NULL;

	len = env_length();
	new_env = malloc(sizeof(char *) * (len + add + 1));

	for (int v = 0; v < len; v++)
		new_env[v] = env[v];

	new_env[len + add] = NULL;

	return (new_env);
}

int _getenvid(const char *name)
{
	int len = 0, index = 0;
	char *name_eq;

	name_eq = str_concat(name, "=");

	len = _strlen(name_eq);

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

void append_env(char *varval)
{
	char **old_env = environ;
	int len = env_length();

	environ = extend_env(environ, 1);
	free(old_env);
	environ[len] = varval;
}

/******** EXPOSED ********/

char **reset_env(void)
{
	char **old = environ;

	environ = stash_env(NULL);
	wipe_env(old);
	local_env = NULL;
	return (environ);
}

void init_env(void)
{
	char *varval = NULL;
	int len = env_length();

	if (!local_env)
	{
		local_env = malloc(sizeof(char *) * (len + 1));
		if (!local_env)
			return;

		for (int v = 0; v < len; v++)
		{
			varval = _strdup(environ[v]);
			local_env[v] = varval;
		}
		local_env[len] = NULL;
		stash_env(environ);
		environ = local_env;
	}
}

void print_env(void)
{
	int i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
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

int _setenv(const char *var, const char *val, int overwrite)
{
	char *varval;
	int i = _getenvid(var);

	varval = compose_varval((char *) var, (char *) val);
	if (i < 0)
		append_env(varval);
	else if (overwrite)
	{
		free(environ[i]);
		environ[i] = varval;
	}

	return (0);
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

void wipe_env(char **env)
{
	int v = 0;

	while (env[v] != NULL)
	{
		free(env[v]);
		v++;
	}
	free(env);
}
