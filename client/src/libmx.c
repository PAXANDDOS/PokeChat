#include "../inc/client.h"

char *mx_str_gettime()
{
    time_t cur_time = time(NULL);
    struct tm *tm_struct = localtime(&cur_time);
    int hours = tm_struct->tm_hour;
    int minutes = tm_struct->tm_min;
    char *tlabel = mx_strnew(6);
    tlabel = mx_strjoin(tlabel, mx_itoa(hours));
    tlabel = mx_strjoin(tlabel, ":");
    if(minutes < 10) 
        tlabel = mx_strjoin(tlabel, "0");
    tlabel = mx_strjoin(tlabel, mx_itoa(minutes));
    free(tm_struct);
    return tlabel;
}

char *mx_strnew(const int size) {
    char *memory = NULL;
    int i = 0;

    if (size < 0)
        return NULL;
    memory = (char *)malloc((size + 1) * sizeof(char));
    while (i < size) {
        memory[i] = '\0';
        i++;
    }
    memory[i] = '\0';
    return memory;
}

char *mx_file_to_str(const char *filename) {
    char *dst = NULL;
    int fd;
    int counter = 0;
    char ch;

    fd = open(filename, O_RDONLY);
    while (read(fd, &ch, 1))
        counter++;
    close(fd);
    fd = open(filename, O_RDONLY);
    dst = mx_strnew(counter);
    for (int i = 0; read(fd, &ch, 1); i++)
        dst[i] = ch;
    close(fd);
    return dst;
}

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL)
        return NULL;
    else if (s1 == NULL)
        return strdup(s2);
    else if (s2 == NULL)
        return strdup(s1);
    else {
        int ns1 = strlen(s1), ns2 = strlen(s2);
        char *new = mx_strnew(ns1 + ns2);

        new = strcpy(new, s1);
        new = strcat(new, s2);
        return new;
    }
}

static void mx_swap_char(char *s1, char *s2)
{
	char temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

static void mx_str_reverse(char *s)
{
	int a = strlen(s);

	for(int i = 0; i < a/2; i++)
		mx_swap_char(&s[i],&s[a-1-i]);
}

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
		return strcpy(result, "0");
	if (number == -2147483648)
		return strcpy(result, "-2147483648");
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
