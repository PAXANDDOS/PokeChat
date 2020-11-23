#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *str1 = s1;
    const unsigned char *str2 = s2;
    unsigned int i = 0;

    if (n == 0)
        return 0;
    else {
        while (str1[i] == str2[i] && i != n) {
            if (str1[i] == '\0' && str2[i] == '\0')
                return 0;
            i++;
        }
        return str1[i] - str2[i];
    }
}
