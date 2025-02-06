# shell v2

## dup2 (man 2)

- output management needs to be carried out before calling `execve`
	- `dup2` helps us achieve this

- `>` creates file and redirects output to it. if it already exist, it will be
  overwritten

### exercises

#### 0. stdout to a file
#### 1. stdout to end of a file
#### 2. file to command stdin

## pipe

## dup2 and pipe

### exercises

#### 3. stdout to command input
#### 4. pipe between two processes
