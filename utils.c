#include <ctype.h>
#include <string.h>
#include "utils.h"

char* ltrim(char* s, int* left_trim_space_count)
{
    *left_trim_space_count = 0;
    while(isspace(*s)) {
        (*left_trim_space_count)++;
        s++;
    }
    return s;
}

char *rtrim(char* s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char* trim(char* s, int* left_trim_space_count)
{
    return rtrim(ltrim(s, left_trim_space_count));
}