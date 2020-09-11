#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VAL 1000

int sum(const bool *x, int n)
{
    int s = 0;

    for (int i = 0; i < n; i++)
        s += x[i];

    return s;
}

int main(void)
{
    bool table[MAX_VAL] = { false };
    int x, rc;
    rc = scanf("%d", &x);

    while (rc == 1)
    {
        if (x > 0)
        {
            table[x-1] = true;
        }
        rc = scanf("%d", &x);
    }

    printf("%d\n", sum(table, MAX_VAL));

    return EXIT_SUCCESS;
}
