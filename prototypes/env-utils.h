#ifndef _ENV_UTILS_
#define _ENV_UTILS_

extern char **environ;

typedef struct _link {
	char *path;
	struct _link *prev;
	struct _link *next;
} linked_path;

linked_path *init_path_chain();

void print_paths();

/* man getenv(3) */
char *_getenv(const char *name);

/* man setenv(3) */
int _setenv( const char *name, const char *value, int overwrite);

/* man unsetenv(3) */
int _unsetenv( const char *name);

#endif /* _ENV_UTILS_ */
