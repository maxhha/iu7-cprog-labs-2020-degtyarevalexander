#include <stdio.h>
#include <stdlib.h>
#include "process.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Accept only 1 argument - file name\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(argv[1], "r");

    double start, end;
    double mean;

    if (find_min_max_interval(f, &start, &end) != OK)
    {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }

    fseek(f, 0, SEEK_SET);

    if (get_mean_on_interval(f, start, end, &mean) != OK)
    {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }

    printf("%0.6lf\n", mean);

    return EXIT_SUCCESS;
}
