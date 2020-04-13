#include <stdio.h>

#define MAX_ARRAY_SIZE 10
#define OK 0
#define INPUT_LEN_ERR 1
#define INPUT_ELEMENTS_ERR 2

int scanf_array(int *a, int **const end)
{
    int n;
    printf("Enter array length:\n");
    int rc = scanf("%d", &n);
    *end = a + n;

    if (rc != 1 || n <= 0 || n > MAX_ARRAY_SIZE)
    {
        return INPUT_LEN_ERR;
    }

    printf("Enter array elements:\n");

    while(a < *end && rc == 1)
    {
        rc = scanf("%d", a++);
    }
    return rc == 1 ? OK : INPUT_ELEMENTS_ERR;
}

int clever_max(const int *a, const int *end)
{
    const int *f = a;
    const int *l = end - 1;
    int max = *f + *l;
    int x;

    while (f <= l)
    {
        x = *f + *l;
        if (x > max)
            max = x;
        f++;
        l--;
    }
    return max;
}

int main(void)
{
    int a[MAX_ARRAY_SIZE];
    int *a_end;
    int rc;

    rc = scanf_array(a, &a_end);

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

    printf("Max is %d\n", clever_max(a, a_end));

    return OK;
}
