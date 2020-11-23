#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
	unsigned char *ptr = (unsigned char *)s + mx_strlen(s);

	while (n--) {
		if (*ptr == (unsigned char)c)
			return ptr;
		ptr--;
	}
	return NULL;
}
