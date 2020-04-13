#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define OK 0
#define INPUT_ERR 1
#define PROCESS_ERR 2

#define MAX_ROWS 10
#define MAX_COLUMNS 10

bool is_valid_size(int rows, int columns)
{
    return (
        rows > 0
        && rows <= MAX_ROWS
        && columns > 0
        && columns <= MAX_COLUMNS);
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

bool is_prime(int x)
{
    x = abs(x);
    if (x < 2)
        return false;

    int limit = (int) sqrt(x) + 1;

    for (int i = 2; i < limit; i++)
        if (x % i == 0)
            return false;

    return true;
}

void filter_primes(int a[][MAX_COLUMNS], int a_rows, int a_columns, int *primes, int *primes_n)
{
    *primes_n = 0;

    for (int r = 0; r < a_rows; r++)
        for (int c = 0; c < a_columns; c++)
            if (is_prime(a[r][c]))
                primes[(*primes_n)++] = a[r][c];
}

void reverse_array(int *a, int n)
{
    int temp;

    for (int i = 0; i < n / 2; i++)
    {
        temp = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = temp;
    }
}

void replace_primes_in(int a[][MAX_COLUMNS], int a_rows, int a_columns, int *to_data, int to_data_len)
{
    int k = 0;
    for (int r = 0; r < a_rows && k < to_data_len; r++)
        for (int c = 0; c < a_columns && k < to_data_len; c++)
            if (is_prime(a[r][c]))
                a[r][c] = to_data[k++];
}

int main(void)
{
    int a[MAX_ROWS][MAX_COLUMNS];
    int a_rows, a_columns;
    int primes[MAX_ROWS * MAX_COLUMNS];
    int primes_n;
    int rc;

    rc = scanf_matrix(a, &a_rows, &a_columns);

    if (rc != OK)
    {
        fprintf(stderr, "Invalid input\n");

        return INPUT_ERR;
    }

    filter_primes(a, a_rows, a_columns, primes, &primes_n);

    if (primes_n == 0)
    {
        fprintf(stderr, "There is no prime numbers\n");

        return PROCESS_ERR;
    }

    reverse_array(primes, primes_n);

    replace_primes_in(a, a_rows, a_columns, primes, primes_n);

    print_matrix(a, a_rows, a_columns);

    return OK;
}
