#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "dec_parser.h"
#include "dec_str.h"

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
char *str_dupcat(const char *prefix, char *suffix)
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

int str_match(char *txt_a, char *txt_b)
{
	int len_a, len_b, match = 0;
	char *dup_a, *dup_b;

	dup_a = str_strip(txt_a);
	dup_b = str_strip(txt_b);

	len_a = str_len(dup_a);
	len_b = str_len(dup_b);

	if (len_a == len_b)
		match = str_nmatch(dup_a, dup_b, len_a);

	free(dup_a);
	free(dup_b);
	return (match);
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

/**
 * _strcmp - compares two strings char by char
 * @s1: first string
 * @s2: you guessed it
 *
 * Return: 0 if strings are equal, otherwise the difference
 */
int _strcmp(const char *s1, const char *s2)
{
	int diff = 0;

	while (1)
	{
		/* compute difference between chars */
		diff = *s1 - *s2;

		/* if end of string or difference is non-zero, break off */
		if (*s1 == '\0' || *s2 == '\0' || diff != 0)
			break;

		s1++; /* increment pointers */
		s2++;
	}

	return (diff); /* difference between strings */
}

/**
 * _strcpy - copies a string from src to dest
 * @dest: destination buffer
 * @src: source string
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	char *start = dest; /* pointer to start of dest */

	if (!dest || !src) /* check for NULL pointers */
		return (dest);

	do
    {
		*dest = *src; /* copy char from src to dest */
		dest++;
	}

    while (*src++ != '\0'); /* formatting seems off */

	return (start); /* gives us a pointer to start of dest */
}

/**
 * _strdup - dupes a string / allocs memory for a copy
 * @str: source string
 *
 * Return: pointer to the newly allocated copy of the string,
 *         or NULL if allocation fails / str is NULL
 */
char *_strdup(const char *str)
{
    char *copy, *p;
    int len = 0;

    if (!str) /* check for NULL pointer */
        return (NULL);

    while (str[len]) /* use Ariel's _strlen? */
        len++;

    copy = malloc(len + 1); /* memory for copy (+1 for null byte) */
    if (!copy)
        return (NULL);

    p = copy; /* pointer to start of copy */
    while (*str)
    {
        *p = *str;
        p++;
        str++;
    }

    *p = '\0'; /* null-terminate copy */

    return (copy); /* shiny new pointer to copy */
}

/**
 * _atoi - converts a string to an integer
 * @s: string to convert
 *
 * Return: integer value of string
 */
int _atoi(const char *s)
{
	int i = 0; /* index */
	int sign = 1; /* sign of number */
	int result = 0; /* result of conversion */

	while ( /* skip whitespace */
		s[i] == ' ' ||
		s[i] == '\t' ||
		s[i] == '\n' ||
		s[i] == '\v' ||
		s[i] == '\f' ||
		s[i] == '\r'
	)
	{
		i++;
	}

	if (s[i] == '-') /* check for negative sign */
	{
		sign = -1; /* set negative sign */
		i++;
	}
	else if (s[i] == '+') /* check for positive sign */
	{
		i++;
	}

	while (s[i] >= '0' && s[i] <= '9') /* convert string */
	{
		result = result * 10 + s[i] - '0'; /* convert digit */
		i++;
	}

	return (result * sign); /* converted value */
}
