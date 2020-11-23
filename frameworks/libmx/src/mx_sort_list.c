#include "libmx.h"

static void swap(void **s1, void **s2) {
    void *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    if (lst && cmp)
        for (t_list *temp1 = lst; temp1; temp1 = temp1->next)
            for (t_list *temp2 = lst; temp2->next; temp2 = temp2->next)
                if (cmp(temp2->data, temp2->next->data))
                    swap(&temp2->data, &temp2->next->data);  
  
    return lst;
}
