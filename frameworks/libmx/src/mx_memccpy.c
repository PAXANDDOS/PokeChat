#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (((const unsigned char *)src)[i] == (unsigned char)c) {
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			return (void *)&(((unsigned char *)dst)[i + 1]);
		} else
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
	}
	return NULL;
}
