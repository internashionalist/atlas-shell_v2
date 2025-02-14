#ifndef _CHEPE_STR_
#define _CHEPE_STR_

char **tokenize(char *text, char *delims, int limit);
int str_nmatch(const char *txt_a, const char *txt_b, int n);
void str_paste(char **dest, const char *source);
char *str_cat(char *pre, char *post);
char *str_dupcat(const char *pre, const char *post);
char *str_dup(const char *text);
int str_len(const char *text);
char *read_line(char *text);
char *str_ncopy(const char *text, int n);
void strmem_init(char **buffer, int size, int value);
char *str_strip(char *text);
void wipe_tokens(char **tokens);
char *str_duptok(char *text, char *delims);

#endif /* _CHEPE_STR_ */
