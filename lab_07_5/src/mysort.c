#include "mysort.h"

#define SWAP(a,b) \
    for (char *lo = a, *hi = b; lo < b; lo++, hi++) \
    { \
        char c = *lo; \
        *lo = *hi; \
        *hi = c; \
    }

void mysort(void *array, size_t n, size_t size, __compar_fn_t cmp)
{
    char *base = (char *) array;
    char *last;
    char *j_next;

    for (char *i = base + (n - 1) * size; i > base; i = last)
        for (char *j = last = base; j < i; j += size)
            if ((*cmp)((void *) j, (void *) (j_next = j + size)) < 0)
                SWAP(last = j, j_next);
}

#undef SWAP
