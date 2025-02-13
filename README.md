# Simple Shell v2 : Electric Boogaloo 

## Contents

- [Synopsis](#synopsis)
- [Features](#features)
- [Use Instructions](#use-instructions)
- [Flowchart](#flowchart)
- [Authors](#authors)

## Synopsis

Simple Shell v2 implements a command-line shell that mimics basic Unix shell functionality. While continuously displaying a prompt ($), it allows users to navigate data and execute a number of commands. The shell can operate in both interactive and non-interactive modes.

## Features

- Comprehensive Error Handling
- Graceful Signals `EOF` and `SIGINT` 
- Execution of Arguments in Command Line
- Built-In Implementation: `exit`, `setenv`, `unsetenv`, `env`, and `cd`
- Environmental Variables: `PATH`, `OLDPWD`, and `HOME`
- Handling of Input/Output Redirections and Command Separators: `> >> < << || ;`
- Handling of Both Single and Connected Piping

## Use Instructions

**Clone into Simple Shell v2 Repository:**

```bash
git clone https://github.com/NecroKnightMare/atlas-shell_v2.git
```

**Open the Shell Directory:**

```bash
cd atlas-shell_v2
```

**Compile Contents:**

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

**Run Shell Program:**

```bash
./hsh
```

## Authors

- Jose "Chepe" Olmos [@chepeniv](https://github.com/chepeniv)<br>
- AlexAndrea "Ariel" Lopez [@NecroKnightMare](https://github.com/NecroKnightMare)<br>
- Taylor "Nash" Thames [@internashionalist](https://github.com/internashionalist/internashionalist/blob/main/README.md)
