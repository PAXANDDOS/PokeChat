#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
	unsigned char *where = NULL;
	unsigned char *what = NULL;

	if (big_len >= little_len && big_len > 0 && little_len > 0) {
		where = (unsigned char *)big;
		what = (unsigned char *)little;
		while (*where) {
			if (mx_memcmp(where, what, little_len - 1) == 0)
				return where;
			where++;
		}
	}
	return NULL;
}
