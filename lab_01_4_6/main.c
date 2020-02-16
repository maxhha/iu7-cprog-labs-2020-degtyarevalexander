#include <stdio.h>
#include <stdlib.h>

int is_on_segment(int x1, int y1, int x2, int y2, int xa, int ya)
{
    return ((y2 - y1) * (x2 - xa) == (y2 - ya) * (x2 - x1) &&
            abs((x1 + x2) - 2*xa) <= abs(x1 - x2) &&
            abs((y1 + y2) - 2*ya) <= abs(y1 - y2));
}

int main()
{
    int x1, y1, x2, y2, xa, ya, rc;

    setbuf(stdout, NULL);
    printf("Segment and point:\n");

    rc = scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &xa, &ya);

    if (rc != 6 || rc == EOF) {
        printf("no no no\n");
        return 1;
    }

    printf("%d\n", is_on_segment(x1, y1, x2, y2, xa, ya));

    return 0;
}
