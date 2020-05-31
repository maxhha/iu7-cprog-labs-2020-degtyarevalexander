#include <stdio.h>
#include "common.h"

struct Student get_from_file(FILE *f, int i)
{
    fseek(f, i * sizeof(struct Student), SEEK_SET);
    struct Student student;
    fread(&student, sizeof(struct Student), 1, f);

    return student;
}

struct Student get_from_array(struct Student *array, int i)
{
    return array[i];
}

void set_in_file(FILE *f, struct Student student, int i)
{
    fseek(f, i * sizeof(struct Student), SEEK_SET);
    fwrite(&student, sizeof(struct Student), 1, f);
}

void set_in_array(struct Student *array, struct Student student, int i)
{
    array[i] = student;
}
