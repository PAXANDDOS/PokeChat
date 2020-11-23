#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *back_list = mx_create_node(data);
    t_list *temp = NULL;
    if (list == NULL || *list == NULL)
        *list = back_list;
    else {
        temp = *list;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = back_list;
    }
}
