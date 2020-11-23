#include "libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (!arr) return -1;
    int counter = 0;

    if (left < right) {
        int k = left;
        int j = right;
        char *pivot = arr[(j + k) / 2];

        while (k <= j) {
            while (mx_strlen(arr[k]) < mx_strlen(pivot)) k++;
            while (mx_strlen(arr[j]) > mx_strlen(pivot)) j--;

            if (k <= j) {
                if (mx_strlen(arr[j]) != mx_strlen(arr[k])) {
                    char *temp = arr[k];
                    arr[k] = arr[j];
                    arr[j] = temp;
                    counter++;
                }
                j--;
                k++;
            }
        }

        counter += mx_quicksort(arr, left, j);
        counter += mx_quicksort(arr, k, right);
    }    
    return counter;
}
