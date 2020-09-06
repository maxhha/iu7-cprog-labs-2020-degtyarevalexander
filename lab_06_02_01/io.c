#include "io.h"

int read_objects_from_file(FILE *f, t_object *objects, int *n)
{
    for (*n = 0; *n < MAX_OBJECTS; (*n)++, objects++)
    {
        char *s = objects->name;
        char c;

        while (fscanf(f, "%c", &c) == 1 &&
            c != '\n' &&
            s < objects->name + MAX_NAME_LEN)
            *s++ = c;

        if (c != '\n' && s == objects->name + MAX_NAME_LEN)
            return ERR;

        *s = '\0';

        if (feof(f))
            return OK;

        if (fscanf(f, "%lf%lf", &objects->weight, &objects->volume) != 2)
            return ERR;

        if (objects->weight < 0 || objects->volume < 0)
            return ERR;

        fseek(f, 1, SEEK_CUR);
    }

    return fgetc(f) == EOF ? OK : ERR;
}

void print_objects(const t_object *objs, const int n)
{
    for (int i = 0; i < n; i++, objs++)
    {
        printf("%s %0.6lf %0.6lf\n", objs->name, objs->weight, objs->volume);
    }
}
