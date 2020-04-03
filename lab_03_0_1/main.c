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

int scanf_matrix(int (*a)[MAX_COLUMNS], int *rows, int *columns)
{
    printf("Enter matrix size:\n");
    int rc = scanf("%d %d", rows, columns);

    if (rc != 2 || rc == EOF || !is_valid_size(*rows, *columns))
    {
        return INPUT_ERR;
    }

    printf("Enter elements:\n");

    for(int i = 0; i < *rows; i++)
    {
        for(int j = 0; j < *columns; j++)
        {
            rc = scanf("%d", *(a + i) + j);
            if (rc != 1 || rc == EOF) {
                return INPUT_ERR;
            }
        }
    }
    return OK;
}

void print_matrix(int (*a)[MAX_COLUMNS], int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int a[MAX_ROWS][MAX_COLUMNS];
    int a_rows, a_columns;
    int rc;

    rc = scanf_matrix(a, &a_rows, &a_columns);

    if (rc != OK)
    {
        fprintf(stderr, "Invalid input\n");
        return INPUT_ERR;
    }

    printf("You enter:\n");

    print_matrix(a, a_rows, a_columns);

    return OK;
}
