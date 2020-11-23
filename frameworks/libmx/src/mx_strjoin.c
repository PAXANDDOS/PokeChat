#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL)
        return NULL;
    else if (s1 == NULL)
        return mx_strdup(s2);
    else if (s2 == NULL)
        return mx_strdup(s1);
    else {
        int ns1 = mx_strlen(s1), ns2 = mx_strlen(s2);
        char *new = mx_strnew(ns1 + ns2);

        new = mx_strcpy(new, s1);
        new = mx_strcat(new, s2);
        return new;
    }
}
