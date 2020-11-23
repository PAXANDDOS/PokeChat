#include "libmx.h"

static int mx_count_letters(const char *s, char c) {
	int i = 0;

	while (s[i] != c && s[i])
		i++;
	return i;
}

char **mx_strsplit(const char *s, char c) {
    int word_length = 0;
    int i = 0;
    char **arr = NULL;

    if (!s)
        return NULL;
    arr = (char **)malloc((mx_count_words(s, c) + 1) * sizeof(char *));
    while ((*s) && (*s != '\0')) {
        if (*s != c) {
            word_length = mx_count_letters(s, c);
            arr[i] = mx_strndup(s, word_length);
            s += word_length;
            i++;
            continue;
        }
        s++;
    }
    arr[i] = NULL;
    return arr;
}
