#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main_create(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "No output filename\n");
        return EXIT_FAILURE;
    }

    struct s_student students[MAX_STUDENTS];
    int students_n;

    if (parse_file(stdin, MAX_STUDENTS, students, &students_n) != OK)
    {
        fprintf(stderr, "Parse input error on %d\n", students_n + 1);
        return EXIT_FAILURE;
    }

    if (students_n == 0)
    {
        fprintf(stderr, "No students\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(argv[1], "wb");

    if (f == NULL)
    {
        fprintf(stderr, "Open file error\n");
        return EXIT_FAILURE;
    }

    if (fwrite(students, sizeof(struct s_student), students_n, f) != students_n)
    {
        fclose(f);
        fprintf(stderr, "Some students hadnt written to file.\n");
        return EXIT_FAILURE;
    }

    fclose(f);
    return EXIT_SUCCESS;
}
