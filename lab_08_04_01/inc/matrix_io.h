#ifndef __MATRIX_IO_H__
#define __MATRIX_IO_H__

#include <stdlib.h>
#include <stdio.h>
#include "log.h"
#include "matrix_memory.h"

matrix_t *scan_matrix(void);
void print_matrix(const matrix_t *m);

#endif // __MATRIX_IO_H__
