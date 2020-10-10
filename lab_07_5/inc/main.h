#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mysort.h"
#include "array.h"

#define MAX_FILE_NAME 256
#define FILTER_ARG "f"
#define PARSE_ARGS_OK 0
#define PARSE_ARGS_ERR 1

int main(int argc, char const *argv[]);

#endif // __MAIN_H__
