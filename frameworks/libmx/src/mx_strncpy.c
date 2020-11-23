#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len)
{
if (len != 0) {
		char *d = dst;
		const char *s = src;
		do {
			if ((*d++ = *s++) == 0) {
				while (--len != 0)
					*d++ = 0;
				break;
			}
		} while (--len != 0);
	}
	return (dst);
}
