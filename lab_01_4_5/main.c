#include <stdio.h>

int main()
{
    int n, i, rc;

    setbuf(stdout, NULL);
    printf("N:\n");

    rc = scanf("%d", &n);

    if (rc != 1 || rc == EOF || n <= 0) {
        printf("no no no\n");
        return 0;
    }

    i = 2;

    while (n != 1)
    {
        if (n % i == 0)
        {
            printf("%d ", i);
            n /= i;
        }
        else
        {
            i += 1;
        }
    }
    printf("\n");

    return 0;
}
