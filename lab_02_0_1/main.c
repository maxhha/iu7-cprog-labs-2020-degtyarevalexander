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

int sum_even_elements(const int *a, const int n, int *const ans)
{
    int s = 0, count = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] % 2 == 0)
        {
            s += a[i];
            count++;
        }
    }

    if (count == 0)
    {
        return PROCESS_ERR;
    }
    *ans = s;

    return OK;
}

int main(void)
{
    int a[MAX_ARRAY_SIZE];
    int n, sum, rc;

    rc = scanf_array(a, &n);

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

    rc = sum_even_elements(a, n, &sum);

    if (rc == PROCESS_ERR)
    {
        printf("No even elements in array.\n");
        return rc;
    }
    else if (rc != OK)
    {
        printf("Unknown code error %d.\n", rc);
        return rc;
    }

    printf("Sum of even elements is %d\n", sum);

    return OK;
}
