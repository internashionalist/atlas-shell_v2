#ifndef _UTIL_ENV_
#define _UTIL_ENV_

extern char **environ;

void init_env(void);
char **reset_env(void);
void print_env(void);

char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

#endif /* _UTIL_ENV_ */
