#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
	unsigned char *tmp = malloc(len);

	tmp = mx_memcpy(tmp, src, len);
	dst = mx_memcpy(dst, tmp, len);
	free(tmp);
	return dst;
}
