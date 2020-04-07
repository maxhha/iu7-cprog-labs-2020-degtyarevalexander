#include <stdio.h>
#include <stdbool.h>

#define OK 0
#define INPUT_ERR 1

#define MAX_ROWS 10
#define MAX_COLUMNS 10

bool is_valid_size(int rows, int columns)
{
    return (
        rows > 0
        && rows <= MAX_ROWS
        && columns > 0
        && columns <= MAX_COLUMNS
        );
}

int scanf_matrix(int a[][MAX_COLUMNS], int *rows, int *columns)
{
    printf("Enter matrix size:\n");
    int rc = scanf("%d %d", rows, columns);

    if (rc != 2 || rc == EOF || !is_valid_size(*rows, *columns))
    {
        return INPUT_ERR;
    }

    printf("Enter elements:\n");

    for (int i = 0; i < *rows; i++)
    {
        for (int j = 0; j < *columns; j++)
        {
            rc = scanf("%d", *(a + i) + j);

            if (rc != 1 || rc == EOF)
            {
                return INPUT_ERR;
            }
        }
    }
    return OK;
}

void print_matrix(int a[][MAX_COLUMNS], int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void get_rows_sums(int a[][MAX_COLUMNS], int rows, int columns, int *sums)
{
    for (int r = 0; r < rows; r++)
    {
        sums[r] = 0;
        for (int c = 0; c < columns; c++)
        {
            sums[r] += a[r][c];
        }
    }
}

void swap_arrays(int *a, int *b, int n)
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void sort_rows_by_weights(int a[][MAX_COLUMNS], int rows, int columns, int *weights)
{
    if (rows < 2) return;

    int l = 0;
    int r = rows - 1;
    int pivot = weights[(l + r) >> 1];
    int temp;

    while (l < r)
    {
        while (weights[l] < pivot) l++;
        while (weights[r] > pivot) r--;

        if (l <= r) {
            temp = weights[l];
            weights[l] = weights[r];
            weights[r] = temp;

            swap_arrays(*(a + l), *(a + r), columns);

            l++;
            r--;
        }
    }
    sort_rows_by_weights(a, r + 1, columns, weights);
    sort_rows_by_weights(a + l, rows - l, columns, weights + l);
}


int main(void)
{
    int a[MAX_ROWS][MAX_COLUMNS];
    int a_rows, a_columns;
    int sums[MAX_ROWS];
    int rc;

    rc = scanf_matrix(a, &a_rows, &a_columns);

    if (rc != OK)
    {
        fprintf(stderr, "Invalid input\n");

        return INPUT_ERR;
    }

    get_rows_sums(a, a_rows, a_columns, sums);

    sort_rows_by_weights(a, a_rows, a_columns, sums);

    print_matrix(a, a_rows, a_columns);

    return OK;
}
