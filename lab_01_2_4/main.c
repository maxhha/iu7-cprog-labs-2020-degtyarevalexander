#include <stdio.h>

int main()
{
    int n, l, p;

    setbuf(stdout, NULL);
    printf("Flat:\n");

    scanf("%d", &n);

    n -= 1;
    p = n / 36 + 1;
    l = n % 36 / 4 + 1;

    printf("Entry: %d\n; Level: %d", p, l);

    return 0;
}
