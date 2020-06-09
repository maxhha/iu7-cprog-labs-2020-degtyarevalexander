#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define OK 0
#define ENOTFOUND -1

int print_file(char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        return ENOTFOUND;
    }

    int n;
    int rc = count_numbers_in_file(f, &n);
    if (rc != OK)
    {
        fclose(f);
        return EFILESIZE;
    }

    NUMBER_TYPE x;
    fread(&x, sizeof(NUMBER_TYPE), 1, f);

    while (feof(f) == 0)
    {
        printf(NUMBER_FORMAT, x);
        fread(&x, sizeof(NUMBER_TYPE), 1, f);
        printf("%c", feof(f) == 0 ? ' ' : '\n');
    }

    fclose(f);

    return OK;
}

int main_print(int argc, char **argv)
{
    if (argc == 0)
    {
        fprintf(stderr, "No filename argument.\n");
        return EXIT_FAILURE;
    }

    int rc = print_file(argv[0]);

    if (rc == ENOTFOUND)
    {
        fprintf(stderr, "File not found.\n");
        return EXIT_FAILURE;
    }
    if (rc == EFILESIZE)
    {
        fprintf(stderr, "File size is invalid.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
