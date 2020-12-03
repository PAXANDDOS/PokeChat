#include "../inc/client.h"

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
