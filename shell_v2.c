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
    ssize_t n_read;

    init_env();

    if (argc > 1)
    {
        inputline = deserialize(&(argv[1]));
        proc_cmds(inputline);  /* process the commands */
    }
    else /* interactive mode */
    {
        print_prompt(NULL);

        while ((n_read = getline(&inputline, &input_len, stdin)) != -1)
        {
            if (n_read > 0 && inputline[n_read - 1] == '\n')
                inputline[n_read - 1] = '\0';

            if (inputline[0] == '\0') /* handle empty input */
            {
                print_prompt(NULL);
                continue;
            }

            proc_cmds(inputline);

            print_prompt(NULL);
        }
    }

    reset_env();     /* free environment */
    free(inputline); /* free getline buffer */

    return 0;
}
