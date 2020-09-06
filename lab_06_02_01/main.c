#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "io.h"
#include "process.h"

#define SHOW_ALL_PREFIX "ALL"

int main(int argc, char const *argv[])
{
    if (argc < 2 || argc > 3)
    {
        return EXIT_FAILURE;
    }
    const char *filename = argv[1];
    const char *prefix = argc < 3 ? NULL : argv[2];

    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        return EXIT_FAILURE;
    }

    t_object objects[MAX_OBJECTS];
    int objects_n = 0;

    if (read_objects_from_file(f, objects, &objects_n) != OK)
    {
        fclose(f);
        return EXIT_FAILURE;
    }
    fclose(f);

    if (objects_n == 0)
    {
        return EXIT_FAILURE;
    }

    if (prefix == NULL)
    {
        qsort(objects, objects_n, sizeof(*objects), compare_objects_by_density);
        print_objects(objects, objects_n);
    }
    else if (strcmp(prefix, SHOW_ALL_PREFIX) == 0)
    {
        print_objects(objects, objects_n);
    }
    else
    {
        objects_n = filter_objects_by_name(objects, objects_n, argv[2]);
        if (objects_n == 0)
        {
            return EXIT_FAILURE;
        }
        print_objects(objects, objects_n);
    }

    return EXIT_SUCCESS;
}
