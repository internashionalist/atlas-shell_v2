#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

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

char *str_dup(char *source)
{
	int len = 0;
	char *duplet;

	while (source[len] != '\0')
		len++;

	duplet = malloc(sizeof(char) * (len + 1));
	str_paste(&duplet, source);

	return (duplet);
}

char **tokenize(char *text, char *delims, int limit)
{
	char **tokens = malloc(sizeof(void *) * limit);
	char *tok;

	tok = strtok(text, delims); /* strtok "consumes" strings */

	int i = 0;
	do {
		tokens[i] = tok;
		tok = strtok(NULL, delims);
	} while ((++i < limit) && (tok != NULL));

	tokens[i] = NULL;

	free(tok);
	return (tokens);
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

char *str_concat(char *pre, char *post)
{
	int a = 0, b = 0;
	char *concat;
	char *tail;

	while (pre[a] != '\0')
		a++;
	while (post[b] != '\0')
		b++;

	concat = malloc(sizeof(concat) * (a + b));
	str_paste(&concat, pre);

	tail = &concat[a];
	str_paste(&tail, post);

	return (concat);
}
