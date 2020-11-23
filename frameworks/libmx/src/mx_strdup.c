#include "libmx.h"

char *mx_strdup(const char *s1)
{
    char *duplicate = mx_strnew(mx_strlen(s1));
    mx_strcpy(duplicate, s1);

    return duplicate;
}
