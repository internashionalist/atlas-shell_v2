#include <unistd.h>
#include <stdio.h>

// Built in for change directory
int change_directory(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "hsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("hsh")
        }
    }
    return 1;
}
// Ariel