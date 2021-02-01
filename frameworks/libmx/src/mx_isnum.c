#include "libmx.h"

bool is_num(char *s) {
    int len = mx_strlen(s);
    for (int i = 0; i < len; i++)
        if (!mx_isdigit(s[i]))
            return false;
    return true;
}
