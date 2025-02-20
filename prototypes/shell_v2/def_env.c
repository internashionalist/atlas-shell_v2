#include "dec_str.h"
#include "dec_env.h"
#include <stdio.h>
#include <stdlib.h>


/******** PRIVATE ********/

char *__compose_varval(char *var, char *val)
{
	char *var_eq = str_dupcat(var, "=");
	char *varval = str_dupcat(var_eq, val);

	free(var_eq);
	return (varval);
}

int __env_length(void)
{
	int len = 0;

	len = 0;
	while (environ[len] != NULL)
		len++;

	return (len);
}

char **__stash_env(char **env)
{
	static char **stash = NULL;

	if (env)
		stash = env;

	return stash;
}

char **__extend_env(char **env, int add)
{
	int len = 0;
	char **new_env = NULL;

	len = __env_length();
	new_env = malloc(sizeof(char *) * (len + add + 1));

	for (int v = 0; v < len; v++)
		new_env[v] = env[v];

	new_env[len + add] = NULL;

	return (new_env);
}

int __getenvid(const char *name)
{
	int len = 0, index = 0;
	char *name_eq;

	name_eq = str_dupcat(name, "=");

	len = str_len(name_eq);

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

char *__getenvp(const char *name)
{
	int index;
	char *envp = NULL;

	index = __getenvid(name);

	if (index > -1)
		envp = environ[index];

	return (envp);
}

void __append_env(char *varval)
{
	char **old_env = environ;
	int len = __env_length();

	environ = __extend_env(environ, 1);
	free(old_env);
	environ[len] = varval;
}

/******** PUBLIC ********/

char **reset_env()
{
	char **old = environ;

	environ = __stash_env(NULL);

	wipe_env(old);

	return (environ);
}

void init_env(void)
{
	static char **local_env = NULL;
	char *varval = NULL;
	int len = __env_length();

	if (!local_env)
	{
		local_env = malloc(sizeof(char **) * (len + 1));

		for (int v = 0; v < len; v++)
		{
			varval = str_dup(environ[v]);
			local_env[v] = varval;
		}
		local_env[len] = NULL;
		__stash_env(environ);
		environ = local_env;
	}
}

char *_getenv(const char *name)
{
	char *value = __getenvp(name);
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
	int i = __getenvid(var);

	varval = __compose_varval((char *) var, (char *) val);
	if (i < 0)
		__append_env(varval);
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
	int index = __getenvid(name);

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
