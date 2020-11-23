#include "libmx.h"

int mx_strlen(const char *s) 
{
    int j = 0;
    char i = s[0];
    while(i != '\0') {
        j++;
        i = s[j];
    }
    return j;
}
