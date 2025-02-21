# Shell v2 : Shell Harder

## Contents

[Synopsis](#synopsis)  
[Features](#features)  
[Use Instructions](#use-instructions)  
[Examples](#examples)  
[Authors](#authors)

## Synopsis

"Shell v2 : Shell Harder" implements a command line shell that mimics basic Unix shell functionality. While continuously displaying a prompt ($), it allows users to navigate data and execute a number of commands. The shell can operate in both interactive mode (typing commands in a loop) and non-interactive mode (receiving commands from a file or piped input).

## Features

- Comprehensive Error Handling
  - Prints clear error messages when commands fail or can’t be found.
  - Handles invalid inputs or empty lines without crashing.
- Built-In Commands
  - exit: Exits the shell. Accepts an optional numeric argument to set the exit status.
  - cd: Changes the current working directory. Supports cd -, cd [dir], and defaults to HOME.
  - env: Displays the current environment variables.
  - setenv: Creates or updates an environment variable (setenv VAR VALUE).
  - unsetenv: Removes an environment variable (unsetenv VAR).
- Environment Variables
  - Automatically recognizes and updates PATH, OLDPWD, and HOME when relevant (e.g. on cd -).
  - Uses _getenv,_setenv, _unsetenv internally for environment management.
- Graceful Signal & EOF Handling
  - SIGINT (Ctrl + C) gracefully interrupts the command but keeps the shell running (no crash).
  - EOF (Ctrl + D) exits the shell with a proper status.
- Command Execution with Arguments
  - Executes commands with flags and arguments (e.g. ls -l /tmp).
  - Searches the directories in PATH if a command is not an absolute or relative path.
- Input & Output Redirection
  - > Redirects stdout to a file (truncate).
  - >> Redirects stdout to a file (append).
  - < Reads stdin from a file.
  - << Supports simple “here doc”-style input in certain builds (not fully tested).
- Logical & Command Separators
  - ; Runs multiple commands sequentially.
  - && (short-circuit AND): Runs the next command only if the previous succeeded.
  - || (short-circuit OR): Runs the next command only if the previous failed.
- Piping
  - Single and connected pipes (e.g., ls -l | grep "txt" | wc -l) are supported.
  - Passes the stdout of one command as the stdin of the next.
- Non-Interactive Mode
  - Can read commands from a file or from standard input.
  - e.g. echo "ls -l" | ./hsh executes ls -l once and then exits.
- Robust Memory Management
  - Freed tokens and temporary strings to avoid leaks.
  - Defensive checks for NULL (missing environment variables, empty lines, etc.).

## Use Instructions

**Clone into Shell v2 Repository:**

```bash
git clone https://github.com/NecroKnightMare/atlas-shell_v2.git
```

**Open the Shell Directory:**

```bash
cd atlas-shell_v2
```

**Run Makefile:**

```bash
make
```

**Run Shell Program:**

```bash
./hsh
```

## Examples

- Basic Commands

```console
$ ./hsh
$ pwd
/home/user/atlas-shell_v2
$ ls -l
total 48
-rw-r--r-- 1 user user  2345 Apr  1 def_cmd.c
-rw-r--r-- 1 user user  1240 Apr  1 def_str.c
...
$ exit
```

- Change Directory

```console
$ cd /usr
$ pwd
/usr
$ cd -
/home/user/atlas-shell_v2
$ cd
$ pwd
/home/user
```

- Environmental Variables

```console
$ env
USER=user
HOME=/home/user
PATH=/usr/local/bin:/usr/bin:/bin
...
```

- Redirection

```bash
$ ls > out.txt
$ cat out.txt
out.txt
def_cmd.c
def_str.c
...
$ echo "Hello" >> out.txt
```

- Command Separators

```bash
$ echo "First"; echo "Second"
First
Second
$ false && echo "will not print"
$ false || echo "this prints because false failed"
This prints because false failed
```

- Piping

```bash
$ ls -l | grep ".c" | wc -l
5
```

- Non-Interactive Execution

```bash
$ echo "echo 'Hello World'" | ./hsh
Hello World
```

## Authors

Jose "Chepe" Olmos [@chepeniv](https://github.com/chepeniv)  
AlexAndrea "Ariel" Lopez [@NecroKnightMare](https://github.com/NecroKnightMare)  
Taylor "Nash" Thames [@internashionalist](https://github.com/internashionalist/internashionalist/blob/main/README.md)
