# C: Shell v2

# Resources

- [wikipedia: Unix Shell](https://en.wikipedia.org/wiki/Unix_shell)
- [wikipedia: Thompson Shell](https://en.wikipedia.org/wiki/Thompson_shell)
- [wikipedia: Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)
- [36.1 Interactive and Non-Interactive Scripts](https://tldp.org/LDP/abs/html/intandnonint.html)
- [lexers vs parsers](https://stackoverflow.com/questions/2842809/lexers-vs-parsers/3614928#3614928)

## intranet concepts

- [shell v1](https://intranet.atlasschool.com/concepts/900)
- [shell v2](https://intranet.atlasschool.com/concepts/919)

# Objectives

- how does a shell work
- what is a `pid` and a `ppid`
- how to manipulate the environment of a given process
- what's the difference between a function call and a system call
- how to create a process
- what are the three prototypes of main
- how does the shell use the `PATH` variable to find programs
- how to execute another program with the `execve` system call
- how to suspend the execution of a process until one of it's children
  terminates
- what is `EOF`
- how to redirect the content of a file into another
- what is a pipeline
- how to setup a pipe
- how to setup a pipe between two processes

# Requirements

- readme.md and authors.md are mandatory at the root of the project
- betty compliance
- no more than five functions per file 😫
- include-guard your headers
- no memory leaks

## Functions and System calls

### syscalls

```c
/* signatures are simplified; consult man 2 pages */

#include <unistd.h>

	int access(char *path, int mode);
	int chdir(char *path);
	int close(int fd);
	int execve(char *path, char *argv[], char *envp[]);
	pid_t fork(void);
	ssize_t read(int fd, void buf[], size_t buf_count);
	ssize_t write(int fd, void buf[], size_t buf_count);
	void _exit(int status);
	int dup(int oldfd);
	int dup2(int oldfd, int newfd);
	int pipe(int pipefd[2]);
	int unlink(char *path);
	int gethostname(char *name, size_t len);
	uid_t geteuid(void);
	pid_t getpid(void);

#include <sys/stat.h>

	int stat(char *path, struct stat *statbuff);   // __xstat
	int fstat(int fd, struct stat *statbuff);      // __fxstat
	int lstat(char *path, struct stat *statbuff);  // __lxstat

#include <signal.h>

	typedef void (*sighandler_t)(int);

	int kill(pid_t pid, int sig);
	sighandler_t signal(int signum, sighandler_t handler);
	int sigaction(
		int signum,
		struct sigaction *act,
		struct sigaction oldact);

#include <fctl.h>

	int open(char *path, int flags, ... /* mode_t mode */ );

#include <sys/wait.h>

	pid_t wait(int *wstatus);
	pid_t waitpid(pid_t pid, int *wstatus, int options);
	pid_t wait3(int *wstatus, int options, struct rusage *rusage);
	pid_t wait4(pid_t pid, int *wstatus, int options, struct *rusage);

#include <time.h>

	time_t time(time_t *tloc);

#include <sys/select.h>

	int select(
		int nfds,
		fd_set *readfds,
		fd_set *writefds,
		fd_set *exceptfds,
		struct timeval *timeout);
```

### libcalls

```c
/* libraries can hold both syscalls and non-syscalls 🌠 tmyk */

#include <signal.h>
	int sigemptyset(sigset_t *set);

#include <sys/types.h>
#include <dirent.h>

	int closedir(DIR *dirp);
	DIR *opendir(char *name);
	struct dirent *readdir(DIR *dirp);

#include <stdlib.h>

	void exit(int status);
	void free(void *ptr);
	void *malloc(size_t size);

#include <unistd.h>

	char *getcwd(char buf[], size_t buf_size);
	int isatty(int fd);

#include <stdio.h>
#include <errno.h>

	void perror(char *s);
	ssize_t getline(char **lineptr, size_t *n, FILE *stream);
	int printf(char *format, ...);
	int fprintf(FILE *stream, char *format);
	int vfprintf(FILE *stream, char *format, va_list ap);
	int sprintf(char *str, char *format, ...);
	int fflush(FILE *stream);

#include <string.h>

	char *strtok(char *str, char *delim);

#include <time.h>

	struct tm *localtime(time_t *timep);

#include <sys/types.h>
#include <pwd.h>

	struct passwd *getpwuid(uid_t uid);
```

### indeterminate

```c
int *__errno_location(void); /* errno macros ? */
```

## Compilation

- provide a makefile in order to compile your program
	- define the `all` that compiles, links, and generates the executable `hsh`
	- the `-Wall` `-Werror` `-Wextra` and `-pedantic` flags are mandatory

# Output

- our shell will by automatically review in non-interactive mode by piping
  commands into it. therefore your prompt will not be taken into account.
- our program must have the exact same `stdout` and `stderr` output as `/bin/sh`
- only difference is when printing an error, the name of the program must be
  equivalent to `argv[0]`

# Testing


