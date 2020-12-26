#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef __USE_DYNLIN__

#include "../deps/lab_07_5/inc/mysort.h"
#include "../deps/lab_07_5/inc/array.h"

#else // __USE_DYNLIN__

#include <dlfcn.h>

#define LIB_PATH "libs/liblab_07_5.so"

typedef int (*dlcompare_numbers_t)(const void *, const void *);
typedef void (*dlmysort_t)(void *array, size_t n, size_t size, dlcompare_numbers_t cmp);
typedef int (*dlread_array_from_file_t)(const char *filename, int **pb_arr, int **pe_arr);
typedef int (*dlwrite_array_to_file_t)(const char *filename, const int *pb_arr, const int *pe_arr);
typedef int (*dlkey_t)(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#define OK 0
#define EREADARRAY -1
#define EWRITEARRAY -2
#define EFILTERARRAY -3

#endif // __USE_DYNLIN__

#define FILTER_ARG "f"
#define PARSE_ARGS_OK 0
#define PARSE_ARGS_ERR 1

#endif // __MAIN_H__
