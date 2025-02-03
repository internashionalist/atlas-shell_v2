#include <stdio.h>
#include <stdlib.h>

size_t my_strlen(const char *str) {
    size_t len = 0;
    // str[len] is equivalent to *(str + len)
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
// Ariel

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
