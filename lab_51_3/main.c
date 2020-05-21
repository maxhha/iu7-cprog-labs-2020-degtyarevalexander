/**
 * This program can:
 *  *   generate binary file with random numbers of int type
 *  *   print values stored in binary file
 *  *   sort values in binary file in ascending order using bubble sort
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "No operation argument passed.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "c") == 0)
    {
        return main_create(argc - 2, argv + 2);
    }

    if (strcmp(argv[1], "p") == 0)
    {
        return main_print(argc - 2, argv + 2);
    }

    if (strcmp(argv[1], "s") == 0)
    {
        return main_sort(argc - 2, argv + 2);
    }

    fprintf(stderr, "Unknown operation argument.\n"
        "Supports: (c)reate, (p)rint, (s)ort.\n");

    return EXIT_FAILURE;
}
