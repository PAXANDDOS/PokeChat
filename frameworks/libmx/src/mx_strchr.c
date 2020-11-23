#include "libmx.h"

char *mx_strchr(const char *s, int c)
{
    do {
        if(*s == c)
            return (char*)s;
    } while (*s++);
    
    return NULL;
}
