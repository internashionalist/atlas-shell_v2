#include <unistd.h>
#include <stdio.h>

// Built in for change directory
int change_directory (const char *pathname, char *old, size_t len)
{

    if (path) {
        fprintf("cd $HOME")
    }
    // self made strlen
    if (path == NULL || my_strlen(path) == 0) 
    {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }
    if (chdir(path) != 0) {
        perror("cd");
    }
}
// Ariel