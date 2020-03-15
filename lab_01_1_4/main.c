#include <stdio.h>

#define OK 0
#define FLATS_PER_LEVEL 4
#define FLATS_PER_ENTRY 36

int main()
{
    int n, l, p;

    setbuf(stdout, NULL);
    printf("Flat:\n");

    scanf("%d", &n);

    n -= 1;
    p = n / FLATS_PER_ENTRY + 1;
    l = n % FLATS_PER_ENTRY / FLATS_PER_LEVEL + 1;

    printf("Entry: %d\nLevel: %d\n", p, l);

    return OK;
}
