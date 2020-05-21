#include <stdio.h>
#include "common.h"

int count_numbers_in_file(FILE *f, int *count)
{
    if (fseek(f, 0, SEEK_END) != 0)
        return EFILESIZE;

    int s = ftell(f);

    if (s <= 0)
        return EFILESIZE;

    if (s % sizeof(NUMBER_TYPE) != 0)
        return EFILESIZE;

    *count = s / sizeof(NUMBER_TYPE);

    if (fseek(f, 0, SEEK_SET) != 0)
        return EFILESIZE;

    return OK;
}
