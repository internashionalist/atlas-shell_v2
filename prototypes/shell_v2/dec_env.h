#ifndef _ENV_
#define _ENV_

int _unsetenv(const char *name);
int _setenv(const char *var, const char *val, int overwrite);
char *_getenv(const char *name);

#endif /* _ENV_ */
