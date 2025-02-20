#ifndef _ENV_
#define _ENV_

extern char **environ;

int _unsetenv(const char *name);
int _setenv(const char *var, const char *val, int overwrite);
char *_getenv(const char *name);
void print_env(void);
void init_env(void);
char **reset_env();
void wipe_env(char **env);

#endif /* _ENV_ */
