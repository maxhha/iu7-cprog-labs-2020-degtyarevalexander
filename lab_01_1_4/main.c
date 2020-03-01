#include <stdio.h>

#define OK 0

int main()
{
    int n, l, p;

    setbuf(stdout, NULL);
    printf("Flat:\n");

    scanf("%d", &n);

    n -= 1;
    p = n / 36 + 1;
    l = n % 36 / 4 + 1;

    printf("Entry: %d\nLevel: %d\n", p, l);

    return OK;
}
