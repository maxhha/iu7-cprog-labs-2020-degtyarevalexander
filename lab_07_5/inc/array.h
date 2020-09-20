#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdlib.h>
#include <stdio.h>

#define OK 0
#define EREADARRAY 2
#define EFILTERARRAY 3

int read_array(FILE *f, int *array[], size_t *array_n);
void write_array(FILE *f, const int *array, const size_t n);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif // __ARRAY_H__
