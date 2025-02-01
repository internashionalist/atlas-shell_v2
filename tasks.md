# Tasks

## 0. README, man, AUTHORS (44pts)

at the root create :

- `README.md`
- `man_1_hsh`
- `AUTHORS.md`

## 1. Betty (20pts)

- pass all `betty-style` and `betty-doc` checks
- all `*.c` and `*.h` will be checked

## 2. hsh 1.0 (52pts)

write a UNIX command line interpreter

### mandatory

- display a prompt and await user input
	- command lines will always end with a new line
- display the prompt again after each command executed
- if no executable can be found, print an error message, display the prompt
  again
- handle errors
- handle the "end-of-file" condition (`Ctrl-D`)
- handle command lines with arguments
- handle and parse the `PATH` environment variable

### builtins

implement the following:
- `exit`
	- must behave exactly as `sh`'s
	- handle arguments
- `cd`
	- change the current directory of the process
	- syntax: `cd [path]`
		- if no path argument is given interpret as `cd $HOME`
	- handle `cd -`
	- update `PWD` every time
- `env`
	- prints the current environment

### optional

- the special characters: `"`, `'`,`` ` ``, `\`, `*`, `&`, `#`
- movable cursor
- handle pipes and redirections

### note:

- there are a lot checks for this task, thus it may take a long time. focus on
  testing locally before submitting to the checker

## 3. hsh 1.1 (6pts)

- handle the right stream redirector `>`
	- usage: `command > output_file`
	- you don't have to handle the `> output_file command` syntax

## 4. ¯\_(ツ)_/¯

## 5. hsh 1.2 (7pts)

- handle the double right stream redirector `>>`
	- usage: `command >> output_file`
	- you don't have to handle the `>> output_file command` syntax

## 6. hsh 1.3 (6pts)

- handle the left stream redirector `<`
	- usage: `command < output_file`
	- you don't have to handle the `< output_file command` syntax

## 7. hsh 1.4 (4pts)

- handle the double left stream redirector `<<` also known as `heredoc`
	- usage: `command << delimeter`
	- you don't have to handle the `<< delimiter command` syntax

## 8. hsh 1.5 (10pts)

- handle the pipe stream redirector `|`
	- usage: `command1 | command2`

## 9. hsh 1.6 (6pts)

- handle the command separator `;`
	- usage: `command1 ; command2`

## 10. hsh 1.7 (8pts)

- handle the logical separator `&&`

## 11. hsh 1.8 (9pts)

- handle the logical separator `||`

## 12. hsh 2.0 (10pts)

implement the following:
- `setenv`
	- initialize a new environment variable, modify existing ones
	- syntax: `setenv VAR VAL`
	- on failure print to `stderr`
- `unsetenv`
	- remove an environment variable
	- syntax: `unsetenv VAR`
	- on failure print to `stderr`
