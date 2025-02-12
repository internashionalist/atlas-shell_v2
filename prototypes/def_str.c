#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int str_len(const char *text)
{
	int len = 0;

	while (text[len] != '\0')
		len++;

	return (len);
}

void str_paste(char **dest, const char *source)
{
	int len = str_len(source);

	for (int c = 0; c <= len; c++)
		(*dest)[c] = source[c];
}

char *str_dup(const char *source)
{
	char *duplet;
	int len = str_len(source);

	duplet = malloc(sizeof(char) * (len + 1));
	str_paste(&duplet, source);

	return (duplet);
}

char *str_concat(const char *prefix, const char *suffix)
{
	int a = 0, b = 0;
	char *concat, *tail;

	a = str_len(prefix);
	b = str_len(suffix);

	concat = malloc(sizeof(char) * (a + b + 1));
	str_paste(&concat, prefix);
	tail = &(concat[a]);
	str_paste(&tail, suffix);

	return (concat);
}

int str_nmatch(const char *txt_a, const char *txt_b, int n)
{
	for(
	int c = 0;
	(c < n) && (txt_a[c] != '\0') && (txt_b[c] != '\0');
	c++)
		if (txt_a[c] != txt_b[c])
			return (0);

	return (1);
}

char **tokenize(char *text, char *delims, int limit)
{
	char **tokens = malloc(sizeof(void *) * limit);
	char *tok;
	int i = 0;

	tok = strtok(text, delims);

	do {
		tokens[i] = tok;
		tok = strtok(NULL, delims);
	} while ((++i < limit) && (tok != NULL));

	tokens[i] = NULL;

	free(tok);
	return (tokens);
}
