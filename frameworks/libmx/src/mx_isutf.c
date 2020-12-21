#include "libmx.h"

bool mx_isutf(wchar_t c){
    setlocale(LC_ALL, "ru_RU.utf8");
    if(c >= 33 && c<= 126)
        return TRUE;
    else if(c == L'А' || c == L'Б')
        return TRUE;
	else return FALSE;
}
