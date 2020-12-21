#include "../inc/client.h"

char *mx_str_gettime()
{
    time_t cur_time = time(NULL);
    tm_struct = localtime(&cur_time);
    int hours = tm_struct->tm_hour;
    int minutes = tm_struct->tm_min;
    char *tlabel = NULL;

    tlabel = mx_strjoin(tlabel, mx_itoa(hours));
    tlabel = mx_strjoin(tlabel, ":");
    if(minutes < 10)
        tlabel = mx_strjoin(tlabel, "0");
    tlabel = mx_strjoin(tlabel, mx_itoa(minutes));

    return tlabel;
}

char *mx_str_getdate()
{
    time_t cur_time = time(NULL);
    tm_struct = localtime(&cur_time);
    int day = tm_struct->tm_mday;
    int month = tm_struct->tm_mon;
    int year = tm_struct->tm_year;
    char *dlabel = NULL;

    if(day < 10) dlabel = mx_strjoin(dlabel, "0");
    dlabel = mx_strjoin(dlabel, mx_itoa(day));

    dlabel = mx_strjoin(dlabel, ".");

    if(month < 10) dlabel = mx_strjoin(dlabel, "0");
    dlabel = mx_strjoin(dlabel, mx_itoa(month+1));

    dlabel = mx_strjoin(dlabel, ".");

    dlabel = mx_strjoin(dlabel, mx_itoa(year+1900));
    return dlabel;
}
