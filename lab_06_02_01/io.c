#include "io.h"

int read_objects_from_file(FILE *f, t_object *objects, int *n)
{
    for (*n = 0; *n < MAX_OBJECTS; (*n)++, objects++)
    {
        char *s = objects->name;
        char *s_end = objects->name + MAX_NAME_LEN;
        int c;

        while ((c = fgetc(f)) != EOF && c != '\n' && s < s_end)
            *s++ = c;

        if (c == EOF)
            return OK;

        if (s == objects->name || (c != '\n' && s == s_end))
            return ERR;

        *s = '\0';

        if (fscanf(f, "%lf%lf", &objects->weight, &objects->volume) != 2)
            return ERR;

        if (objects->weight <= 0 || objects->volume <= 0)
            return ERR;

        fgetc(f);
    }

    return fgetc(f) == EOF ? OK : ERR;
}

void print_objects(const t_object *objs, const int n)
{
    for (int i = 0; i < n; i++, objs++)
    {
        printf("%s\n%0.6lf\n%0.6lf\n", objs->name, objs->weight, objs->volume);
    }
}
