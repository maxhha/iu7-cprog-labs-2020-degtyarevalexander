#include <stdio.h>

#define OK 0
#define ENOTFOUND -1
#define EFILESIZE -2

#define NUMBER_TYPE int
#define NUMBER_FORMAT "%d"

int count_numbers_in_file(FILE *f, int *count);
