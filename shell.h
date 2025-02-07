#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define TOK_SIZE 128
#define DELIM " \t\r\n:"

typedef struct info_shell_st
{
    int line_num; /* tracks current line number for error messages */
} info_t;

/* prototypes */

int tokenize_input(char *input, char ***tokens)
int change_directory (const char *pathname, char *old, size_t len)
void prompt(void);
int shell_loop(info_t *info);
int execute(char **args, info_t *info);

#endif /* SHELL_H */
