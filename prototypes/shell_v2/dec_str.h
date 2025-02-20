#ifndef _STR_
#define _STR_

char **tokenize(char *text, char *delims, int limit);
char *str_cat(char *prefix, char *suffix);
char *str_dup(const char *source);
char *str_dupcat(char *prefix, const char *suffix);
char *str_duptok(char *text, char *delims);
char *str_ncopy(const char *text, int n);
char *str_strip(char *text);
int str_len(const char *text);
int str_nmatch(const char *txt_a, const char *txt_b, int n);
void str_paste(char **dest, const char *source);
int find_string(char **strings, char *str);

void strmem_init(char **buffer, int size, int value);
void strmem_realloc(char *buffer, int add);

#endif /* _STR_ */
