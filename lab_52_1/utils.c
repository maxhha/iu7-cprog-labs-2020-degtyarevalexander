#include <stdio.h>
#include "common.h"

void printf_student(FILE *f, struct Student student)
{
    fprintf(
        f,
        "%s %s %d %d %d %d\n",
        student.last_name,
        student.first_name,
        student.marks[0],
        student.marks[1],
        student.marks[2],
        student.marks[3]);
}
