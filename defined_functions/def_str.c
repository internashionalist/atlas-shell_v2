#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "util_str.h"

void str_paste(char **dest, const char *source)
{
	int c = 0;

	while (source[c] != '\0')
	{
		(*dest)[c] = source[c];
		c++;
	}

	(*dest)[c] = '\0';
}

char *_strdup(const char *source)
{
	int len = 0;
	char *duplet;

	if (!source)
		return (NULL);

	while (source[len] != '\0')
		len++;

	duplet = malloc(sizeof(char) * (len + 1));
	if (!duplet)
		return (NULL);

	str_paste(&duplet, source);

	return (duplet);
}

char **tokenize(char *text, char *delims, int limit)
{
	char **tokens = malloc(sizeof(void *) * limit);
	char *tok;

	tok = strtok(text, delims);

	int i = 0;
	do {
		tokens[i] = tok;
		tok = strtok(NULL, delims);
	} while ((++i < limit) && (tok != NULL));

	tokens[i] = NULL;

	/* removed free(tok) - not dynamicallyk allocated */
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

char *str_concat(const char *pre, const char *post)
{
	int a = 0, b = 0;
	char *concat;
	char *tail;

	while (pre[a] != '\0')
		a++;
	while (post[b] != '\0')
		b++;

	concat = malloc((a + b + 1) * sizeof(char)); /* both str + NULL */
	if (!concat)
		return (NULL);
	str_paste(&concat, pre);

	tail = &concat[a];
	str_paste(&tail, post);

	return (concat);
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

/*
 * _strlen - returns the length of a string
 * @text: string to measure
 *
 * Return: length of string
 */
int _strlen(const char *text)
{
	int len = 0;

	while (text[len] != '\0')
		len++;

	return (len);
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
