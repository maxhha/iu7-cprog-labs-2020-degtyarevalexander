#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 10
#define M 8

void scanf_matrix(int b[][M], int *n_rows, int *n_columns)
{
    *n_columns = M;
    *n_rows = 0;
    int x;
    int col;
    int rc = scanf("%d", &x);

    while (rc == 1 && *n_rows < N)
    {
        for (col = 0; x > 0; col++)
        {
            b[*n_rows][col] = x % 10;
            x /= 10;
        }

        while (col < M)
        {
            b[*n_rows][col++] = 0;
        }

        (*n_rows)++;

        rc = scanf("%d", &x);
    }
}

int *find_min_even_number(const int b[][M], int n_rows, int n_columns)
{
    const int *min = NULL;

    for (int r = 0; r < n_rows; r++)
        for (int c = 0; c < n_columns; c++)
            if (b[r][c] % 2 == 0 && (min == NULL || *min > b[r][c]))
                min = &b[r][c];

    return (int *) min;
}

void print_matrix_market(const int b[][M], int n_rows, int n_columns)
{
    int non_zero = 0;
    for (int r = 0; r < n_rows; r++)
        for (int c = 0; c < n_columns; c++)
            non_zero += b[r][c] != 0;

    printf("%d %d %d\n", n_rows, n_columns, non_zero);

    for (int r = 0; r < n_rows; r++)
        for (int c = 0; c < n_columns; c++)
            if (b[r][c] != 0)
                printf("%d %d %d\n", r+1, c+1, b[r][c]);

}

int main(void)
{
    int b[N][M];
    int n_rows;
    int n_columns;

    scanf_matrix(b, &n_rows, &n_columns);

    int *min_even = find_min_even_number((const int (*)[M]) b, n_rows, n_columns);

    if (min_even == NULL)
    {
        printf("%% no even numbers\n");
    }
    else
    {
        printf("%% min even number = %d\n", *min_even);
    }

    print_matrix_market((const int (*)[M]) b, n_rows, n_columns);

    return EXIT_SUCCESS;
}
