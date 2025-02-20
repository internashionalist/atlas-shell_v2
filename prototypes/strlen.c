#include <stdio.h>

size_t my_strlen(const char *str) {
    size_t len = 0;
    // str[len] is equivalent to *(str + len)
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
// Ariel