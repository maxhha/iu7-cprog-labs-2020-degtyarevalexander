#include <stdio.h>

#define MAX_ARRAY_SIZE 10
#define OK 0
#define INPUT_LEN_ERR 1
#define INPUT_ELEMENTS_ERR 2
#define PROCESS_ERR 3

int scanf_array(int *a, int *const len)
{
    printf("Enter array length:\n");
    int rc = scanf("%d", len);

    if (rc != 1 || *len <= 0 || *len > MAX_ARRAY_SIZE)
    {
        return INPUT_LEN_ERR;
    }

    printf("Enter array elements:\n");

    for (int i = 0; i < *len; i++)
    {
        rc = scanf("%d", a + i);

        if (rc != 1 || rc == EOF)
        {
            return INPUT_ELEMENTS_ERR;
        }
    }
    return OK;
}

void print_array(const int *a, const int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

double get_average(const int *a, const int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        s += a[i];
    }
    return (double) s / n;
}

void copy_greater(const int *a, const int n, const double threshold, int *out_a, int *const out_n)
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > threshold)
        {
            out_a[j++] = a[i];
        }
    }
    *out_n = j;
}

int main(void)
{
    int a[MAX_ARRAY_SIZE], b[MAX_ARRAY_SIZE];
    int n_a, n_b, rc;

    rc = scanf_array(a, &n_a);

    if (rc == INPUT_LEN_ERR)
    {
        printf("Array size is invalid.\n");
        return rc;
    }
    else if (rc == INPUT_ELEMENTS_ERR)
    {
        printf("Oops! It was a bad element.\n");
        return rc;
    }
    else if (rc != OK)
    {
        printf("Unknown code error %d.\n", rc);
        return rc;
    }

    copy_greater(a, n_a, get_average(a, n_a), b, &n_b);

    if (n_b == 0)
    {
        printf("No greater than elements average.\n");
        return PROCESS_ERR;
    }

    print_array(b, n_b);

    return OK;
}
