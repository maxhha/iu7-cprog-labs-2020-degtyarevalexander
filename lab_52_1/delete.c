#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"

#define TYPE array
#define IN_TYPE struct s_student *
#include "delete_template.c"
#undef TYPE
#undef IN_TYPE

int main_delete_text(int argc, char **argv)
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

    students_n = delete_array(students, students, students_n);

    fseek(f, 0, SEEK_SET);

    for (int i = 0; i < students_n; i++)
    {
        printf_student(f, students[i]);
    }

    fflush(f);
    ftruncate(fileno(f), ftell(f));

    fclose(f);

    return EXIT_SUCCESS;
}

#define TYPE file
#define IN_TYPE FILE *
#include "delete_template.c"
#undef TYPE
#undef IN_TYPE

int main_delete_bin(int argc, char **argv)
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

    students_n = delete_file(f, f, students_n);

    fflush(f);
    ftruncate(fileno(f), students_n * sizeof(struct s_student));
    fclose(f);

    return EXIT_SUCCESS;
}
