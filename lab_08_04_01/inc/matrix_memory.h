#ifndef __MATRIX_MEMORY_H__
#define __MATRIX_MEMORY_H__

#include <stdlib.h>
#include "log.h"
#include "matrix_typedef.h"

matrix_t *create_matrix(size_t width, size_t height);
void free_matrix(matrix_t *m);

#endif // __MATRIX_MEMORY_H__
