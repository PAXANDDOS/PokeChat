#include "libmx.h"

int mx_get_char_index(const char *str, char c) 
{
    if (!str)
        return -2;
    else {
        for (int i = 0; str[i]; i++)
            if (str[i] == c)
                return i;
        return -1;
    }
}
