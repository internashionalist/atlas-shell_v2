#ifndef _UTIL_PATH_
#define _UTIL_PATH_

#include "util_env.h"

typedef struct _link {
	char *path;
	struct _link *prev;
	struct _link *next;
} linked_path;

char *navigate_path();
void print_paths();

linked_path *init_path_chain();
linked_path *nav_path_chain(linked_path *head);
void erase_path_chain(linked_path *head);

#endif /* _UTIL_PATH_ */
