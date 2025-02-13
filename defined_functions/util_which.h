#ifndef _UTIL_WHICH_
#define _UTIL_WHICH_

#include <sys/stat.h>

char *_which(char *basename);
char *build_fullpath(char *dirname, char *filename);
int analyze_paths(char **paths, char *filename);
int print_fullpath(char *fullpath, struct stat *st);
int verify_fullpath(char *fullpath);

#endif /* _UTIL_WHICH_ */
