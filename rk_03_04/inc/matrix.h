#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <stdio.h>
#include "log.h"

typedef struct {
    int *data;
    int width;
    int height;
} matrix_t;

matrix_t *create_matrix(int w, int h);
void free_matrix(matrix_t *m);
matrix_t *read_matrix(char *filename);
int count_neighboors(const matrix_t *m, int x, int y);
matrix_t *get_count_neighboors_matrix(const matrix_t *m);
matrix_t *cut_empty_columns(const matrix_t *m);
int write_matrix(char *filename, const matrix_t *m);

#endif // __MATRIX_H__
