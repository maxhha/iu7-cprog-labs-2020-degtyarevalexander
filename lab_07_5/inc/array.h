#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdlib.h>
#include <stdio.h>

#define OK 0
#define EREADARRAY 2
#define EWRITEARRAY 3
#define EFILTERARRAY 4

int read_array(FILE *f, int **pb_array, int **pe_array);
int read_array_from_file(const char *filename, int **pb_array, int **pe_array);

void write_array(FILE *f, const int *pb_array, const int *pe_array);
int write_array_to_file(const char *filename, const int *pb_array, const int *pe_array);

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif // __ARRAY_H__
