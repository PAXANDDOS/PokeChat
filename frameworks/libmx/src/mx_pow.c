#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
    double result = 1;

    if (pow == 0)
        return result;
    else if (pow > 0)
        for (unsigned int i = 0; i < pow; i++)
            result *= n;
    return result;
}
