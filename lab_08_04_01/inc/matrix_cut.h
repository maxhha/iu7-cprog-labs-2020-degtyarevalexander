#ifndef __MATRIX_OPERATION_H__
#define __MATRIX_OPERATION_H__

#include <stdlib.h>
#include <stdarg.h>
#include "log.h"
#include "matrix_memory.h"

int cut_matrix(matrix_t *m);
int cut_matrixes(int n, ...);

#endif // __MATRIX_OPERATION_H__
