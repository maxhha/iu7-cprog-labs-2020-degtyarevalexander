#include <stdio.h>
#include "common.h"

struct s_student get_from_file(FILE *f, int i)
{
    fseek(f, i * sizeof(struct s_student), SEEK_SET);
    struct s_student student;
    fread(&student, sizeof(struct s_student), 1, f);

    return student;
}

struct s_student get_from_array(struct s_student *array, int i)
{
    return array[i];
}

void set_in_file(FILE *f, struct s_student student, int i)
{
    fseek(f, i * sizeof(struct s_student), SEEK_SET);
    fwrite(&student, sizeof(struct s_student), 1, f);
}

void set_in_array(struct s_student *array, struct s_student student, int i)
{
    array[i] = student;
}
