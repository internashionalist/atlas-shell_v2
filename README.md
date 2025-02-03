# $\color{Mulberry}{SIMPLE\ SHELL\ }$ 

a simple shell takes user input from the command line and interprets it from a path to correctly output from bin directory. 

## $\color{Mulberry}{Features\ }$
	
Limits or to use string library <string.h> and custom functions.
	
## $\color{Mulberry}{Motivation\ }$

This program is to recreate a shell but in its simplicity to utilize our knowledge thusfar in a group project consisting of two students. Concepts used were functions, function pointers, static libraries, MACROS, recursion, localization and global variables.

	
## $\color{Mulberry}{Code\ Language\ }$

Language C for the functions and ROFF for the man page.
	
## $\color{Mulberry}{Framework\ }$

Works in Windows 11 Ubuntu 22.04, MAC, and Linux.
	
## $\color{Mulberry}{Code\ Example\ }$
	
	if (pid == 0) /** child process through fork*/
	{
		if (execvp(command, args) == -1)
		{
			perror("Failed to execute custom command");
			exit(EXIT_FAILURE);
		}
	}
	
## $\color{Mulberry}{Installation\ }$

Make sure the latest Windows, Mac, Linux is installed in your operating system. This code was compiled with gcc, so install this if you do not have it already installed.	

    Compile it using gcc std=gnu89

	
1. + Copy the code into the files desired for the program.
2. + Compile it gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
3. + After successfully compiling, type ./hsh
4. + Start typing commands!
	
## $\color{Mulberry}{Tests\ }$
	
All tests done in Visual Studios. Compiled differently in VS and had to recompose code to compile with std=gnu89. Useed ./ tests to test if functions/files worked, used valgrind to check for memory links and valgrind ggdb3 for detailed errors.
	
## $\color{Mulberry}{How\ To\ Use\ }$

After compiling successfully and code runs as it should type ./hsh and your prompt should show on a new line. 

* + Type in a command such as ls -la, grep, cat, yes, echo, rm, etc...

* + + if unsure of where to find directoory, type ls and bin, zsh, bash are directories that could pop up. type cd .. until you are in the bin directory. Type ls aand a long list of commands should appear to give you an idea of what command are executable.

* + After typing command uou should see the condition being executed and be provided with a new line, to continue the loop.

* + If done type ctl + c to end the program.

## $\color{Mulberry}{Contribute\ }$

@Simple atlas-simple_shell
@NecroKnightMare atlas-simple_shell

## $\color{Mulberry}{Credits\ }$

Atlas School (Holberton) has created this project for students to utilize to create unique code. This one is done by Malik Vance and Ariel Lopez.

## $\color{Mulberry}{License\ }$

MIT © Jose (Chepe) Olmos | AlexAndrea (Ariel) Lopez | Nash Thames

## $\color{Mulberry}{Flowchart\ }$
