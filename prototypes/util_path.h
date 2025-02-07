#ifndef _UTIL_PATH_
#define _UTIL_PATH_

#include <sys/stat.h>

typedef struct _link {
	char *path;
	struct _link *prev;
	struct _link *next;
} linked_path;

int is_pathed(char *cmdpath);
char *navigate_path();
void print_paths();

char *build_fullpath(char *dirname, char *filename);
int verify_fullpath(char *fullpath);
int analyze_paths(char **paths, char *filename);

linked_path *init_path_chain();
linked_path *nav_path_chain(linked_path *head);
void erase_path_chain(linked_path *head);

#endif /* _UTIL_PATH_ */
