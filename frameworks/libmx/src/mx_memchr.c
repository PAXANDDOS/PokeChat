#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
	unsigned char *ptr = (unsigned char *)s;

	while (n > 0) {
		if (*ptr == (unsigned char)c)
			return ptr;
		ptr++;
		n--;
	}
	return NULL;
}
