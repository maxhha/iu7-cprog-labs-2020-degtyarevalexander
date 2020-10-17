#include <math.h>
#include <string.h>
#include "process.h"
#include <stdio.h>

int compare_objects_by_density(const void *a, const void *b)
{
    t_object *obj_a = (t_object *) a;
    t_object *obj_b = (t_object *) b;

    double density_a = obj_a->weight / obj_a->volume;
    double density_b = obj_b->weight / obj_b->volume;

    if (fabs(density_a - density_b) < EPS)
        return 0;
    if (density_a > density_b)
        return 1;
    return -1;
}

int filter_objects_by_name(t_object *objects, int n, const char *name)
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (strstr(objects[i].name, name) == objects[i].name)
        {
            objects[k++] = objects[i];
        }
    }
    return k;
}
