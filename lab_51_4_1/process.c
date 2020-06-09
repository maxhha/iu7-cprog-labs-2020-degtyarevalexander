#include <stdio.h>
#include "process.h"

int process(FILE *f, int *count)
{
    *count = 0;
    int a, b, c;

    if (fscanf(f, "%d %d %d", &a, &b, &c) != 3)
    {
        return EINPUT;
    }

    do
    {
        *count += a < b && c < b;
        a = b;
        b = c;
    } while (fscanf(f, "%d", &c) == 1);

    return OK;
}
