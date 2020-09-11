#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 10
#define M 8

void scanf_matrix(char b[][M], int *n_rows, int *n_columns)
{
    *n_columns = M;
    *n_rows = 0;
    char s[M+1];
    char *i;
    int c = 0;

    int rc = scanf("%s", s);

    while (rc != EOF)
    {
        c = 0;
        for (i = s; *i != '\0'; i++)
        {
            b[*n_rows][c++] = *i;
        }

        while (c < M)
        {
            b[*n_rows][c++] = '0';
        }

        (*n_rows)++;

        rc = scanf("%s", s);
    }
}

char *find_min_even_number(const char b[][M], int n_rows, int n_columns)
{
    const char *min = NULL;

    for (int r = 0; r < n_rows; r++)
        for (int c = 0; c < n_columns; c++)
            if ((b[r][c] - '0') % 2 == 0 && (min == NULL || *min > b[r][c]))
                min = &b[r][c];

    return (char *) min;
}

void print_matrix_market(const char b[][M], int n_rows, int n_columns)
{
    int non_zero = 0;
    for (int r = 0; r < n_rows; r++)
        for (int c = 0; c < n_columns; c++)
            non_zero += b[r][c] != '0';

    printf("%d %d %d\n", n_rows, n_columns, non_zero);

    for (int r = 0; r < n_rows; r++)
        for (int c = 0; c < n_columns; c++)
            if (b[r][c] != '0')
                printf("%d %d %c\n", r+1, c+1, b[r][c]);

}

int main(void)
{
    char b[N][M];
    int n_rows;
    int n_columns;

    scanf_matrix(b, &n_rows, &n_columns);

    char *min_even = find_min_even_number((const char (*)[M]) b, n_rows, n_columns);

    if (min_even == NULL)
    {
        printf("%% no even numbers\n");
    }
    else
    {
        printf("%% min even number = %c\n", *min_even);
    }

    print_matrix_market((const char (*)[M]) b, n_rows, n_columns);

    return EXIT_SUCCESS;
}
