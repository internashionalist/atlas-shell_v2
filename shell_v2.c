#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "dec_cmd.h"
#include "dec_exit.h"
#include "dec_env.h"
#include "dec_parser.h"
#include "dec_path.h"
#include "dec_str.h"
#include "dec_util.h"
#include "dec_cd.h"
#include "dec_builtins.h"

void print_prompt(char *prompt)
{
    if (!prompt)
        prompt = "$ ";
    if (isatty(STDIN_FILENO))  /* interactive mode */
        printf("%s", prompt);
}

int main(int argc, char **argv)
{
    char *inputline = NULL;
    size_t input_len = 0;
    char **input_tokens = NULL;
    ssize_t n_read;

    init_env();

    if (argc > 1)
    {
        inputline = deserialize(&(argv[1]));
        proc_cmds(inputline);  /* process the commands */
    }
    else
    {
        print_prompt(NULL);
        while ((n_read = getline(&inputline, &input_len, stdin)) > -1)
        {
            if (n_read > 0 && inputline[n_read - 1] == '\n')  /* remove newline */
                inputline[n_read - 1] = '\0';

            input_tokens = tokenize(inputline, " \t", 1024);

            if (!input_tokens || !input_tokens[0])  /* handle empty input */
            {
                free(input_tokens);
                continue;
            }

            if (is_builtin(input_tokens)) 
            {
                handle_builtin(input_tokens);  /* process built-in command */
            }
            else
            {
                char *cmd_cpy = _strdup(input_tokens[0]);
                proc_cmds(inputline);  /* process complex commands (pipe, redirection) */
                free(cmd_cpy);
            }

            free(input_tokens);
            print_prompt(NULL);
        }
    }

    reset_env();
    free(inputline);

    return 0;
}
