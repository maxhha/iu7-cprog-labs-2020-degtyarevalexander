#include <stdio.h>

#define MAX_ARRAY_SIZE 10
#define OK 0
#define INPUT_LEN_ERR 1
#define INPUT_ELEMENTS_ERR 2

int scanf_array(int a[], int *len)
{
    int n;
    printf("Enter array length:\n");
    int rc = scanf("%d", &n);
    *len = n;

    if (rc != 1 || n <= 0 || n > MAX_ARRAY_SIZE)
    {
        return INPUT_LEN_ERR;
    }

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++)
    {
        rc = scanf("%d", &a[i]);

        if (rc != 1 || rc == EOF)
        {
            return INPUT_ELEMENTS_ERR;
        }
    }
    return OK;
}

void print_array(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void sort_array(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int x = a[i];
        int j = i;
        while (j > 0 && a[j-1] > x)
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = x;
    }
}

int main(void)
{
    int a[MAX_ARRAY_SIZE];
    int n_a, rc;

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

    sort_array(a, n_a);

    print_array(a, n_a);

    return OK;
}
