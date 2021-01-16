#include "libmx.h"

void mx_clear_list(t_list **list) {
    t_list *p;
    while (*list) {
        p = NULL;
        if (list) {
            p = (*list)->next;
            free(*list);
            *list = p;
        }
    }
}
