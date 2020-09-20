#ifndef __MYSORT_H__
#define __MYSORT_H__

#include "stdlib.h"

void mysort(void *array, size_t n, size_t size, __compar_fn_t cmp);

#endif // __MYSORT_H__
