#include <stdio.h>
#include <stdbool.h>

#define OK 0
#define INPUT_ERR 1
#define NOT_FOUND_ERR 2

#define MAX_ROWS 10
#define MAX_COLUMNS 10

bool is_valid_size(int rows, int columns)
{
    return (
        rows > 0
        && rows <= MAX_ROWS
        && columns > 0
        && columns <= MAX_COLUMNS
        && columns == rows);
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

int find_min(int a[][MAX_ROWS], int rows, int columns, bool (*predicat)(int, int, int), int *result)
{
    int min;
    bool first = true;

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            if (predicat(a[r][c], c, r) && (first || min > a[r][c]))
            {
                min = a[r][c];
                first = false;
            }

    if (first)
    {
        return NOT_FOUND_ERR;
    }

    *result = min;
    return OK;
}

bool is_valid(int val, int x, int y)
{
    return (val & 1) && (y > x);
}

int main(void)
{
    int a[MAX_ROWS][MAX_COLUMNS];
    int a_rows, a_columns;
    int min_value;
    int rc;

    rc = scanf_matrix(a, &a_rows, &a_columns);

    if (rc != OK)
    {
        fprintf(stderr, "Invalid input\n");

        return INPUT_ERR;
    }

    rc = find_min(a, a_rows, a_columns, is_valid, &min_value);

    if (rc != OK)
    {
        fprintf(stderr, "Minimum wasn`t found\n");

        return NOT_FOUND_ERR;
    }

    printf("%d\n", min_value);

    return OK;
}
