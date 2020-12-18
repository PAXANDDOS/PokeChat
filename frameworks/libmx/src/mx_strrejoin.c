#include "libmx.h"

char *mx_strrejoin(char *s1, char const *s2) {
     char *p = NULL;

    if (!s1 && !s2)
        return NULL;
    else if (!s1)
        p = mx_strdup(s2);
    else if (!s2)
        p = mx_strdup(s1);
    else {
        p = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
        if (!p)
            return NULL;
        p = mx_strcpy(p, s1);
        p = mx_strcat(p, s2);
    }
    mx_strdel(&s1);
    return p;
}
