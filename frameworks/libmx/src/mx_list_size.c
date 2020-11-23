#include "libmx.h"

int mx_list_size(t_list *list) 
{
    int counter = 0;
    t_list *tmp = NULL;

    if (list) {
        tmp = list;
        while (tmp != NULL) {
            counter++;
            tmp = tmp->next;
        }
    }
    return counter;
}
