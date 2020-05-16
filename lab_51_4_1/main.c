#include <stdio.h>
#include <stdlib.h>
#include "process.h"

int main(void)
{
    int count;

    if (process(stdin, &count) != OK)
    {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }
    else
    {
        printf("%d\n", count);
    }

    return EXIT_SUCCESS;
}
