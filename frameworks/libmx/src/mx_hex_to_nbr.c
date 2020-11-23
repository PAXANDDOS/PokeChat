#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
	int len = 0;
	unsigned long num = 0;
	unsigned long base = 1;

	if (hex != NULL)
		while (hex[len])
			len++;
	else
		return num;
	for (int i = 0; i <= len; i++) {
		if (hex[len - i] >= '0' && hex[len - i] <= '9') {
			num = num + (hex[len - i] - 48) * base;
			base = base * 16;
		}
		if (hex[len - i] >= 'A' && hex[len - i] <= 'F') {
			num = num + (hex[len - i] - 55) * base;
			base = base * 16;
		}
		if (hex[len - i] >= 'a' && hex[len - i] <= 'f') {
			num = num + (hex[len - i] - 87) * base;
			base = base * 16;
		}
	}
	return num;
}
