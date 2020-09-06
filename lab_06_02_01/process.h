#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "common.h"

int compare_objects_by_density(const void *a, const void *b);
int filter_objects_by_name(t_object *objects, int n, const char *name);

#endif // __PROCESS_H__
