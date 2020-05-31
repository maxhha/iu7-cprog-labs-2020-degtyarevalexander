#include <stdio.h>
#include "common.h"

struct s_Student get_from_file(FILE *f, int i)
{
    fseek(f, i * sizeof(struct s_Student), SEEK_SET);
    struct s_Student student;
    fread(&student, sizeof(struct s_Student), 1, f);

    return student;
}

struct s_Student get_from_array(struct s_Student *array, int i)
{
    return array[i];
}

void set_in_file(FILE *f, struct s_Student student, int i)
{
    fseek(f, i * sizeof(struct s_Student), SEEK_SET);
    fwrite(&student, sizeof(struct s_Student), 1, f);
}

void set_in_array(struct s_Student *array, struct s_Student student, int i)
{
    array[i] = student;
}
