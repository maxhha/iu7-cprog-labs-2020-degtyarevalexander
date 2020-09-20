#include "../inc/array.h"

int read_array(FILE *f, int **array, size_t *array_n)
{
    int numb, rc;
    size_t n = 0;

    while ((rc = fscanf(f, "%d", &numb)) == 1)
        n++;

    if (rc != EOF || n == 0)
        return EREADARRAY;

    int *i = *array = (int *) malloc(n * sizeof(int));

    if (i == NULL)
        return EREADARRAY;

    fseek(f, 0, SEEK_SET);

    while (fscanf(f, "%d", i) == 1)
        i++;

    *array_n = n;

    return OK;
}

void write_array(FILE *f, const int *array, const size_t n)
{
    const int *end = array + n;
    for (const int *i = array; i < end; i++)
        fprintf(f, "%d\n", *i);
}

#include <stdio.h>

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pe_src <= pb_src)
        return EFILTERARRAY;

    size_t n = 0;
    long long int sum = *(pe_src - 1);

    for (const int *i = pe_src - 2; i >= pb_src; i--)
    {
        n += *i > sum;
        sum += *i;
    }

    if (n == 0)
        return EFILTERARRAY;

    *pb_dst = (int *) malloc(n * sizeof(int));

    if (pb_dst == NULL)
        return EFILTERARRAY;

    *pe_dst = *pb_dst + n;
    int *p = *pe_dst - 1;

    sum = *(pe_src - 1);

    for (const int *i = pe_src - 2; i >= pb_src; i--)
    {
        if (*i > sum)
            *p-- = *i;

        sum += *i;
    }

    return OK;
}
