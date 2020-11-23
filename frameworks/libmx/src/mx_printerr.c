#include "libmx.h"

void mx_printerr(const char *s)
{
	int j = 0;
    char i = s[0];
    while(i != '\0') 
	{
    	j++;
    	i = s[j];
    }
	write(2, s, j);
}
