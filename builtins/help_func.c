#include <stdio.h>
#include <stdlib.h>

int change_directory(char **args);
int help_cmd(char **args);
int shell_exit(char **args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &change_directory,
    &help_cmd,
    &shell_exit
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(*char);
}

int change_directory(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("hsh")
        }
    }
    return 1;
}

int help_cmd(char **args) {
    int i;
    printf("HSH\n");
    printf("Type program names and arguments and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < num_builtins(); i++) {
        printf(" %s\n", builtin_str[i]);
    }
    printf("use the man command for info. \n");
    return 1;
}

int shell_exit(char **args) {
    return 0;
}

int shell_execute(char **args) {
    int i;

    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < num_builtins(); i++) {
        if (_strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return 
}