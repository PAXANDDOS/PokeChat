#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int size2 = mx_strlen(needle);      
    int size1 = mx_strlen(haystack);

    for (int count = 0; count<size1; haystack++, count++) {
        char *temp = mx_strchr(haystack, haystack[0]);

        if(mx_strncmp(temp,needle,size2)==0)
            return (char*)haystack;
    }
    return NULL;
}
