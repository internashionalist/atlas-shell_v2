#ifndef _STR_
#define _STR_

char *str_cat(char *prefix, char *suffix);
char *str_dup(const char *source);
char *str_dupcat(const char *prefix, char *suffix);
char *str_duptok(char *text, char *delims);
char *str_ncopy(const char *text, int n);
char *str_strip(char *text);
int str_len(const char *text);
int str_nmatch(const char *txt_a, const char *txt_b, int n);
void str_paste(char **dest, const char *source);
int find_string(char **strings, char *str);
int str_match(char *txt_a, char *txt_b);

void strmem_init(char **buffer, int size, int value);
void strmem_realloc(char *buffer, int add);

#endif /* _STR_ */
