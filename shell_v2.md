# C: Shell v2

# Resources

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

```
access
chdir
close
execve
fork
stat (__xstat)
lstat (__lxstat)
fstat (__fxstat)
kill
open
read
signal
wait
waitpid
wait3
wait4
write
_exit
dup
dup2
pipe
unlink
time
gethostname
geteuid
sigaction
sigemptyset
select
getpid
__errno_location (errno macros)
closedir
exit
free
getcwd
getline
malloc
opendir
perror
readdir
strtok
localtime
getpwuid
isatty
printf
fflush
fprintf
vfprintf
sprintf
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


