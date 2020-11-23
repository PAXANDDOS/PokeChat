#include "libmx.h"

int mx_count_words(const char *str, char c) {
    bool state = true;
    unsigned wordcount = 0;
    int i = 0;
    
    if (str == NULL)
        return -1;
    else {
        while (str[i]) {
            if (str[i] == c)
                state = true;
            else if (state == true) {
                state = false;
                ++wordcount;
            }
            ++i;
        }
        return wordcount;
    }
}
