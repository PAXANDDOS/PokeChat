#include "libmx.h"

static int number_length(int number) {
	int length = 0;

	while (number) {
		number /= 10;
		length++;
	}
	return length;
}

char *mx_itoa(int number) {
	int length = number_length(number);
	int tmp = number;
	char *result = NULL;

	result = mx_strnew(length);
	if (number == 0)
		return mx_strcpy(result, "0");
	if (number == -2147483648)
		return mx_strcpy(result, "-2147483648");
	tmp = number;
	for (int i = 0; i < length; i++) {
		if (tmp < 0) {
			result[length] = '-';
			tmp = -tmp;
		}
		result[i] = (tmp % 10) + '0';
		tmp /= 10;
	}
	mx_str_reverse(result);
	return result;
}
