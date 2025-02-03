#include <unistd.h>
#include <stdio.h>

int change_directory (const char *pathname)
{
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