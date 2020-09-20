#ifndef __MYSORT_H__
#define __MYSORT_H__

#include "stdlib.h"

#define OK 0
#define ESORT 10

int mysort(void *array, size_t n, size_t size, int (*cmp)(const void *, const void *));

#endif // __MYSORT_H__
