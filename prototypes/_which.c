#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

char **tokenize(char *text, char *delims)
{
	int max_tokens = 64;
	char **tokens = malloc(sizeof(void *) * max_tokens);
	char *tok = strtok(text, delims);

	int i = 0;
	do {
		tokens[i] = tok;
		tok = strtok(NULL, delims);
	} while ((++i < max_tokens) && (tok != NULL));

	tokens[i] = NULL;

	free(tok);
	return (tokens);
}

int str_nmatch(char *txt_a, char *txt_b, int n)
{
	for(
	int c = 0;
	(c < n) && (txt_a[c] != '\0') && (txt_b[c] != '\0');
	c++)
		if (txt_a[c] != txt_b[c])
			return (0);

	return (1);
}

char *get_PATH(char **env)
{
	char *path = "PATH=";

	for (int v = 0; env[v] != NULL; v++)
		if (str_nmatch(path, env[v], 5))
			return env[v];

	return (NULL);
}

int verify_path(char *filename, struct stat *st)
{
	if (stat(filename, st) == 0)
	{
		printf("%s\n", filename);
		return (0);
	}
	else
		return (-1);
}

void str_paste(char **dest, char *source)
{
	int c = 0;

	while (source[c] != '\0')
	{
		(*dest)[c] = source[c];
		c++;
	}

	(*dest)[c] = '\0';
}

char *build_path(char *pre, char *post)
{
	int a = 0, b = 0;
	char *concat;
	char *tail;

	while (pre[a] != '\0')
		a++;
	while (post[b] != '\0')
		b++;

	concat = malloc(sizeof(concat) * (a + b + 1));
	str_paste(&concat, pre);

	tail = &concat[a];
	str_paste(&tail, "/");

	tail = &concat[a + 1];
	str_paste(&tail, post);

	return (concat);
}

int analyze_paths(char **paths, char *filename)
{
	struct stat st;
	char *fullpath;
	int err = 0;

	for (int p = 1; paths[p] != NULL; p++)
	{
		fullpath = build_path(paths[p], filename);
		if (verify_path(fullpath, &st) < 0)
		{
			free(fullpath);
			err = -1;
		}
		else
		{
			err = 0;
			break;
		}
	}

	free(fullpath);

	return (err);
}

int main(int count, char **args, char **env)
{
	char *pathvar, **paths;
	int err = 0;

	if (count < 2)
		return (1);

	pathvar = get_PATH(env);
	paths = tokenize(pathvar, "=:");

	for (int a = 1; a < count; a++)
		if (analyze_paths(paths, args[a]) < 0)
			err = 1;

	free(paths);

	return (err);
} /* bpm */
