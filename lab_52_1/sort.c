#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define TYPE array
#define IN_TYPE struct s_student *
#include "sort_template.c"
#undef TYPE
#undef IN_TYPE

int main_sort_text(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "No input filename\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(argv[1], "r+a");

    if (f == NULL)
    {
        fprintf(stderr, "File open error\n");
        return EXIT_FAILURE;
    }

    struct s_student students[MAX_STUDENTS];
    int students_n;

    if (parse_file(f, MAX_STUDENTS, students, &students_n) != OK)
    {
        fclose(f);
        fprintf(stderr, "Parse error on %d\n", students_n + 1);
        return EXIT_FAILURE;
    }

    if (students_n == 0)
    {
        fclose(f);
        fprintf(stderr, "No students\n");
        return EXIT_FAILURE;
    }

    sort_array(students, students_n);
    fseek(f, 0, SEEK_SET);

    for (int i = 0; i < students_n; i++)
    {
        printf_student(stdout, students[i]);
        printf_student(f, students[i]);
    }
    fclose(f);

    return EXIT_SUCCESS;
}

#define TYPE file
#define IN_TYPE FILE *
#include "sort_template.c"
#undef TYPE
#undef IN_TYPE

int main_sort_bin(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "No input filename\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(argv[1], "rb+a");

    if (f == NULL)
    {
        fprintf(stderr, "File open error\n");
        return EXIT_FAILURE;
    }

    fseek(f, 0, SEEK_END);
    int size = ftell(f);

    if (size % sizeof(struct s_student) != 0 || size <= 0)
    {
        fclose(f);
        fprintf(stderr, "File size is incorrect\n");
        return EXIT_FAILURE;
    }
    fseek(f, 0, SEEK_SET);
    int students_n = size / sizeof(struct s_student);

    sort_file(f, students_n);

    fseek(f, 0, SEEK_SET);
    struct s_student student;

    for (int i = 0; i < students_n; i++)
    {
        fread(&student, sizeof(struct s_student), 1, f);
        printf_student(stdout, student);
    }

    fclose(f);

    return EXIT_SUCCESS;
}
