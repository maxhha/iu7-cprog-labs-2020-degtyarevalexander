#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK 0
#define INPUT_ERR 1
#define PROCESS_ERR 2

#define MAX_ROWS 10
#define MAX_COLUMNS 10
#define MAGIC_VALUE 100

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

bool is_starting_with_digit(int x, int digit)
{
    x = abs(x);
    while (x > 9)
    {
        x /= 10;
    }
    return x == digit;
}

bool is_ending_with_digit(int x, int digit)
{
    return abs(x) % 10 == digit;
}

bool is_match_magic_pattern(int *a, int n, int digit)
{
    int number_starts = 0;
    int number_ends = 0;

    for (int *i = a; i < a + n; i++)
    {
        number_starts += is_starting_with_digit(*i, digit);
        number_ends += is_ending_with_digit(*i, digit);
    }

    return (number_starts == number_ends) && (number_ends != 0);
}

void copy_array(int *src, int *dest, int n)
{
    int *p_src = src;
    int *p_dest = dest;
    while (p_src < src + n)
    {
        *(p_dest++) = *(p_src++);
    }
}

void fill_array_with_magic(int *a, int n)
{
    for (int *p = a; p < a + n; p++)
    {
        *p = MAGIC_VALUE;
    }
}

int magic_update(int a[][MAX_COLUMNS], int *rows, int *columns, int digit)
{
    bool matching_rows[MAX_ROWS];
    int new_rows = *rows;

    int (*a_row)[MAX_COLUMNS] = a;
    bool *m_row = matching_rows;

    while (a_row < a + *rows)
    {
        *m_row = is_match_magic_pattern(*a_row, *columns, digit);
        new_rows += *m_row;
        a_row++;
        m_row++;
    }

    if (new_rows > MAX_ROWS) {
        return PROCESS_ERR;
    }

    a_row = a + *rows - 1;
    m_row = matching_rows + *rows - 1;

    for (int (*na_row)[MAX_COLUMNS] = a + new_rows - 1; na_row >= a; na_row--)
    {
        if (*m_row)
        {
            *m_row = false;
            fill_array_with_magic(*na_row, *columns);
            continue;
        }
        copy_array(*(a_row--), *na_row, *columns);
        m_row--;
    }

    *rows = new_rows;

    return OK;
}

int main(void)
{
    int a[MAX_ROWS][MAX_COLUMNS];
    int a_rows, a_columns;
    int digit;
    int rc;

    rc = scanf_matrix(a, &a_rows, &a_columns);

    if (rc != OK)
    {
        fprintf(stderr, "Invalid input\n");

        return INPUT_ERR;
    }

    printf("Enter digit:\n");

    rc = scanf("%d", &digit);

    if (rc != 1 || rc == EOF || digit < 0 || digit > 9)
    {
        fprintf(stderr, "Invalid input\n");

        return INPUT_ERR;
    }

    rc = magic_update(a, &a_rows, &a_columns, digit);

    if (rc != OK)
    {
        fprintf(stderr, "Matrix update error\n");

        return PROCESS_ERR;
    }

    print_matrix(a, a_rows, a_columns);

    return OK;
}
