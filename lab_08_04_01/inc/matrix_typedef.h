#ifndef __MATRIX_TYPEDEF_H__
#define __MATRIX_TYPEDEF_H__

#include <stdlib.h>

typedef struct
{
    int *data;
    size_t width;
    size_t height;
}
matrix_t;

#endif // __MATRIX_TYPEDEF_H__
