#ifndef __MATRIX_MUL_H__
#define __MATRIX_MUL_H__

#include "log.h"
#include "matrix_memory.h"

matrix_t *multiply_matrix(const matrix_t *a, const matrix_t *b);
matrix_t *get_matrix_power(const matrix_t *m, size_t pwr);

#endif // __MATRIX_MUL_H__
