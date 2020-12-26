#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OK 0
#define NOACTION -1
#define MEMERROR -3

int rotate(void *array, size_t nmemb, size_t size, size_t left_shift)
{
    char *base = (char *) array;
    left_shift %= nmemb;

    if (left_shift == 0)
        return OK;

    size_t shift_size = left_shift * size;
    size_t total_size = nmemb * size;
    char *tmp = malloc(shift_size);

    if (tmp == NULL)
        return MEMERROR;

    memcpy(tmp, base, shift_size);
    memmove(base, base + shift_size, total_size - shift_size);
    memcpy(base + total_size - shift_size, tmp, shift_size);

    free(tmp);
    return OK;
}

size_t copy_full_squares(int *array, size_t array_n, int *result)
{
    size_t n = 0;

    for (size_t i = 0; i < array_n; i++)
    {
        int a = array[i], x = (int) sqrt((double) a);

        if (x * x == a)
        {
            if (result != NULL)
                result[n] = a;
            n += 1;
        }
    }

    return n;
}
