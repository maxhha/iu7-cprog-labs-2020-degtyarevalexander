#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define OK 0
#define ENOTFOUND -1
#define EFILESIZE -2

int count_numbers_in_file(FILE *f, int *count)
{
    if (fseek(f, 0, SEEK_END) != 0)
        return EFILESIZE;

    int s = ftell(f);

    if (s < 0)
        return EFILESIZE;

    if (s % sizeof(NUMBER_TYPE) != 0)
        return EFILESIZE;

    *count = s / sizeof(NUMBER_TYPE);

    if (fseek(f, 0, SEEK_SET) != 0)
        return EFILESIZE;

    return OK;
}

NUMBER_TYPE get_number_by_pos(FILE *f, int pos)
{
    fseek(f, pos * sizeof(NUMBER_TYPE), SEEK_SET);
    NUMBER_TYPE x;
    fread(&x, sizeof(NUMBER_TYPE), 1, f);
    return x;
}

void set_number_by_pos(FILE *f, int pos, NUMBER_TYPE number)
{
    fseek(f, pos * sizeof(NUMBER_TYPE), SEEK_SET);
    fwrite(&number, sizeof(NUMBER_TYPE), 1, f);
}

int sort(FILE *f)
{
    int n;
    int rc = count_numbers_in_file(f, &n);

    if (rc != OK)
    {
        return EFILESIZE;
    }

    NUMBER_TYPE a, b;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            a = get_number_by_pos(f, j);
            b = get_number_by_pos(f, j + 1);
            if (a > b)
            {
                set_number_by_pos(f, j, b);
                set_number_by_pos(f, j + 1, a);
            }
        }
    }

    return OK;
}

int sort_file(char *filename)
{
    FILE *f = fopen(filename, "r+b");
    if (f == NULL)
    {
        return ENOTFOUND;
    }

    int rc = sort(f);

    fclose(f);

    return rc;
}

int main_sort(int argc, char **argv)
{
    if (argc == 0)
    {
        fprintf(stderr, "No filename argument.\n");
        return EXIT_FAILURE;
    }

    int rc = sort_file(argv[0]);

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

    // printf("Successful.\n");
    return EXIT_SUCCESS;
}
