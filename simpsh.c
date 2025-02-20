#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "dec_cmd.h"
#include "dec_env.h"
#include "dec_parser.h"
#include "dec_path.h"
#include "dec_str.h"
#include "dec_util.h"
#include "dec_exit.h"
#include "dec_cd.h"

void print_prompt(char *prompt)
{
    if (!prompt)
        prompt = "$ ";
    if (isatty(STDIN_FILENO)) /* interactive mode */
        printf("%s", prompt);
}

int process_cmd(char **input_tokens)
{
    int wstatus;
    char *command = input_tokens[0];
    char *fullpath = NULL;

    if (command[0] == '.' || command[0] == '/') /* absolute PATH */
    {
        if (access(command, X_OK) == 0)
            fullpath = _strdup(command);
        else
            return (-1);
    }
    else
    {
        fullpath = _which(command); /* search PATH for command */
        if (!fullpath)
            return (-1);
    }

    input_tokens[0] = fullpath; /* replace with complete path */
    pid_t pid = fork(); /* create a child process */
    
    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }

    if (pid == 0) /* child process */
    {
        if (execve(input_tokens[0], input_tokens, environ) == -1)
        {
            perror("execve");
            exit(127);
        }
    }
    else
    {
        wait(&wstatus); /* wait for the child process to finish */
    }

    free(fullpath); /* free allocated memory in parent process */
    return (wstatus);
}

int main(int argc, char **argv)
{
    char *inputline = NULL;
    size_t input_len = 0;
    char **input_tokens = NULL;
    ssize_t n_read;

    init_env();

    if (argc > 1) /* non-interactive mode */
    {
        inputline = deserialize(&(argv[1]));
        proc_cmds(inputline);
    }
    else /* interactive mode */
    {
        print_prompt(NULL);
        while ((n_read = getline(&inputline, &input_len, stdin)) > -1)
        {
            if (n_read > 0 && inputline[n_read - 1] == '\n') /* remove newline */
                inputline[n_read - 1] = '\0';

            input_tokens = tokenize(inputline, " \t", 1024);
            
            if (!input_tokens || !input_tokens[0]) /* handle empty input */
            {
                free(input_tokens);
                continue;
            }

            if (_strcmp(input_tokens[0], "exit") == 0)
            {
                exit_shell(input_tokens); /* exit built-in */
            }
            else if (_strcmp(input_tokens[0], "cd") == 0)
            {
                change_dir(input_tokens); /* cd built-in */
            }
            else if (_strcmp(input_tokens[0], "env") == 0)
            {
                print_env(); /* env built-in */
            }
            else
            {
                char *cmd_cpy = _strdup(input_tokens[0]); 
                int status = process_cmd(input_tokens); 
                if (status == -1)
                    printf("Command not found: %s\n", input_tokens[0]);
                free(cmd_cpy);
            }

            free(input_tokens);
            print_prompt(NULL);
        }
    }

    reset_env();
    free(inputline);
    
    return (0);
}