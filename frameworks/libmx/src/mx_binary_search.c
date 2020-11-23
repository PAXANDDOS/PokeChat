#include "libmx.h"

int mx_binary_search(char** arr, int size, const char *s, int *count)
{ 
    int l = 0 ; 
    int r = size - 1; 
    int coun = 0;
    while (l <= r)  
    { 
        coun++;
        *count = coun;
        int m = l + (r - l) / 2; 
        int res = 1;
        if (mx_strcmp(s, arr[m]) == 0) res = 0; 
        if (res == 0) return m; 
        if (mx_strcmp(s, arr[m]) > 0) l = m + 1; 
        else r = m - 1; 
    } 
    *count = 0;
    return -1; 
}
