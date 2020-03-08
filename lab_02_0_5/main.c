#include <stdio.h>

#define MAX_ARRAY_SIZE 10
#define OK 0
#define INPUT_LEN_ERR 1
#define INPUT_ELEMENTS_ERR 2

int scanf_array(int a[], int **right)
{
    int n;
    printf("Enter array length:\n");
    int rc = scanf("%d", &n);
    *right = a + n;

    if (rc != 1 || n <= 0 || n > MAX_ARRAY_SIZE)
    {
        return INPUT_LEN_ERR;
    }

    printf("Enter array elements:\n");

    for (int *i = a; i < *right; i++)
    {
        rc = scanf("%d", i);

        if (rc != 1 || rc == EOF)
        {
            return INPUT_ELEMENTS_ERR;
        }
    }
    return OK;
}

int clever_max(int a[], int *r_a)
{
    int *l = a;
    int *r = r_a - 1;
    int max = *l + *r;
    while (l <= r)
    {
        int x = *l + *r;
        if (x > max)
            max = x;
        l++;
        r--;
    }
    return max;
}

int main(void)
{
    int a[MAX_ARRAY_SIZE];
    int *r_a;
    int rc;

    rc = scanf_array(a, &r_a);

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

    printf("Max is %d\n", clever_max(a, r_a));

    return OK;
}
