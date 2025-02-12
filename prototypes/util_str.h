#ifndef _CHEPE_STR_
#define _CHEPE_STR_

char **tokenize(char *text, char *delims, int limit);
int str_nmatch(const char *txt_a, const char *txt_b, int n);
void str_paste(char **dest, const char *source);
char *str_concat(const char *pre, const char *post);
char *str_dup(const char *text);
int str_len(const char *text);

#endif /* _CHEPE_STR_ */
