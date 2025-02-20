#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int find_string(char **strings, char *str)
{
	int index = -1;

	while (strings[index] != NULL)
		if (strings[index] == str)
			break;

	return (index);
}

int str_len(const char *text)
{
	int c;

	for (c = 0; text[c] != 0; ++c);

	return (c);
}

void str_paste(char **dest, const char *source)
{
	int len = str_len(source);

	for (int c = 0; c < len; c++)
		(*dest)[c] = source[c];

	(*dest)[len] = '\0';
}

void strmem_init(char **buffer, int size, int value)
{
	int index;

	for (index = 0; index < size; index++)
		(*buffer)[index] = value;
}

char *str_dup(const char *source)
{
	char *duplet;
	int len = str_len(source);

	duplet = malloc(sizeof(char) * (len + 1));
	str_paste(&duplet, source);

	return (duplet);
}

/*  leaves prefix alone and returns a duplicate concat string*/
char *str_dupcat(char *prefix, const char *suffix)
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

/* frees prefix and returns a new malloc string*/
char *str_cat(char *prefix, char *suffix)
{
	char *concat = str_dupcat(prefix, suffix);

	free(prefix);

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

char *str_duptok(char *text, char *delims)
{
	char *tok;

	tok = strtok(text, delims);
	tok = str_dup(tok);

	return (tok);
}

char *str_ncopy(const char *text, int n)
{
	int c = 0;
	char *copy;

	copy = malloc(sizeof(char) * n + 1);

	while ((c < n) && (text[c] != '\0'))
	{
		copy[c] = text[c];
		c++;
	}

	copy[c] = '\0';

	return (copy);
}

void strmem_realloc(char *buffer, int add)
{
	int len;
	char *new_buffer;

	len = str_len(buffer);
	len = len + add + 1;

	new_buffer = malloc(sizeof(char) * len);
	strmem_init(&new_buffer, len, 0);
	str_paste(&new_buffer, buffer);
	free(buffer);
}

char *str_strip(char *text)
{
	int w = 0;
	char **words, *sentence, *whitespace = " \t\n";

	/* prepare memory */
	sentence = malloc(sizeof(char)* 1);
	strmem_init(&sentence, 1, 0);

	/* create and break duplicate at whitespaces */
	text = str_dup(text);
	words = tokenize(text, whitespace, 2048);

	/* reconstruct with collapsed whitespace */
	while (words[w + 1] != NULL)
	{
		sentence = str_cat(sentence, words[w]);
		sentence = str_cat(sentence, " ");
		w++;
	}
	sentence = str_cat(sentence, words[w]);

	free(text);
	free(words);

	return (sentence);
}

/* MOVE DEFINITIONS OUT */
