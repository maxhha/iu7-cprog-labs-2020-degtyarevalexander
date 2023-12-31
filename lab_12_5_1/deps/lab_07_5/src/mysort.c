#include "../inc/mysort.h"

int compare_numbers(const void *a, const void *b)
{
    int a_num = *(int *) a;
    int b_num = *(int *) b;
    return a_num < b_num ? -1 : a_num == b_num ? 0 : 1;
}

#define SWAP(a,b) \
    for (char *lo = a, *hi = b; lo < b; lo++, hi++) \
    { \
        char c = *lo; \
        *lo = *hi; \
        *hi = c; \
    }

void mysort(void *array, size_t n, size_t size, int (*cmp)(const void *, const void *))
{
    char *base = (char *) array;
    char *last;
    char *j_next;

    if (size == 0 || n == 0 || array == NULL || cmp == NULL)
        return;

    for (char *i = base + (n - 1) * size; i > base; i = last)
        for (char *j = last = base; j < i; j += size)
            if ((*cmp)((void *) j, (void *) (j_next = j + size)) > 0)
                SWAP(last = j, j_next);
}

#undef SWAP
