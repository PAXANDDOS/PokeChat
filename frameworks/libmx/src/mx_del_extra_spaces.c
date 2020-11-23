#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    char *memory = NULL;
    char *temp = NULL;
    int i = 0;
    int j = 0;

    if (!str) return NULL;
    
    memory = mx_strnew(mx_strlen(str));
    while (str[i]) {
        if (!(mx_isspace(str[i]))) {
            memory[j] = str[i];
            j++;
        }
        if (!(mx_isspace(str[i])) && mx_isspace(str[i + 1])) {
            memory[j] = ' ';
            j++;
        }
        i++;
    }
    temp = mx_strtrim(memory);
    mx_strdel(&memory);
    return temp;
}
