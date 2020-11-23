#include "libmx.h"

int mx_bubble_sort(char** arr, int size)
{
    char *temp; 
    int counter = 0;

    for (int j=0; j<size-1; j++) 
    { 
        for (int i=j+1; i<size; i++) 
        { 
            if (mx_strcmp(arr[j], arr[i]) > 0) 
            { 
                temp = arr[j]; 
                arr[j] =arr[i]; 
                arr[i] = temp; 
                counter++;
            } 
        } 
    } 
    return counter;
}
