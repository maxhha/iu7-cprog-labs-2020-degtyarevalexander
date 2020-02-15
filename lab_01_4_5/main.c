#include <stdio.h>

int main()
{
    int n, i;

    setbuf(stdout, NULL);
    printf("N:\n");

    scanf("%d", &n);

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
