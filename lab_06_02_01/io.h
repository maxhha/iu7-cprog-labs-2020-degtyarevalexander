#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include "common.h"

int read_objects_from_file(FILE *f, t_object *objects, int *n);
void print_objects(const t_object *objects, const int n);

#endif // __IO_H__
