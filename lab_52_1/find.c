#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define TYPE array
#define IN_TYPE struct s_Student *
#include "find.c.template"
#undef TYPE
#undef IN_TYPE

int main_find_text(int argc, char **argv)
{
    if (argc < 4)
    {
        fprintf(stderr, "Not enough arguments\n");
        return EXIT_FAILURE;
    }

    FILE *f_in = fopen(argv[1], "r");

    if (f_in == NULL)
    {
        fprintf(stderr, "File open error\n");
        return EXIT_FAILURE;
    }

    struct s_Student students[MAX_STUDENTS];
    int students_n;

    if (parse_file(f_in, MAX_STUDENTS, students, &students_n) != OK)
    {
        fclose(f_in);
        fprintf(stderr, "Parse error on %d\n", students_n + 1);
        return EXIT_FAILURE;
    }
    fclose(f_in);

    if (students_n == 0)
    {
        fprintf(stderr, "No students\n");
        return EXIT_FAILURE;
    }

    students_n = find_array(students, students, students_n, argv[3]);

    if (students_n == 0)
    {
        fprintf(stderr, "No students were found\n");
        return EXIT_FAILURE;
    }

    FILE *f_out = fopen(argv[2], "w");

    if (f_out == NULL)
    {
        fprintf(stderr, "Output file open error\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < students_n; i++)
    {
        printf_student(f_out, students[i]);
    }

    return EXIT_SUCCESS;
}



#define TYPE file
#define IN_TYPE FILE *
#include "find.c.template"
#undef TYPE
#undef IN_TYPE

int main_find_bin(int argc, char **argv)
{
    if (argc < 4)
    {
        fprintf(stderr, "Not enough arguments\n");
        return EXIT_FAILURE;
    }

    FILE *f_in = fopen(argv[1], "rb");

    if (f_in == NULL)
    {
        fprintf(stderr, "File open error\n");
        return EXIT_FAILURE;
    }

    fseek(f_in, 0, SEEK_END);
    int size = ftell(f_in);

    if (size % sizeof(struct s_Student) != 0 || size <= 0)
    {
        fclose(f_in);
        fprintf(stderr, "File size is incorrect\n");
        return EXIT_FAILURE;
    }
    fseek(f_in, 0, SEEK_SET);
    int students_n = size / sizeof(struct s_Student);

    FILE *f_out = fopen(argv[2], "wb");

    if (f_out == NULL)
    {
        fclose(f_in);
        fprintf(stderr, "Output file open error\n");
        return EXIT_FAILURE;
    }

    students_n = find_file(f_in, f_out, students_n, argv[3]);

    fclose(f_in);
    fclose(f_out);

    if (students_n == 0)
    {
        fprintf(stderr, "No students were found\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
