#ifndef UTIL_STR_H
#define UTIL_STR_H

#include <stdlib.h>

char **tokenize(char *text, char *delims, int limit);
int str_nmatch(const char *txt_a, const char *txt_b, int n);
void str_paste(char **dest, const char *source);
char *str_concat(const char *pre, const char *post);
char *str_dup(const char *text);
int str_len(const char *text);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
int _atoi(const char *s);

#endif /* UTIL_STR_H */
