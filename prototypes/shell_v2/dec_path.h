#ifndef _PATH_
#define _PATH_

#include <sys/stat.h>

int is_pathed(char *cmdpath);
char *navigate_path(void);
int verify_fullpath(char *fullpath);
char *build_fullpath(char *dirname, char *filename);

#endif /* _PATH_ */
