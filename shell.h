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

/* prototypes */

int tokenize_input(char *input, char ***tokens)

#endif /* SHELL_H */
