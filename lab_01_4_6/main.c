#include <stdio.h>
#include <stdlib.h>

int is_on_segment(int x1, int y1, int x2, int y2, int xa, int ya)
{
    return ((y2 - y1) * (x2 - xa) == (y2 - ya) * (x2 - x1) &&
        abs((x1 + x2) - 2 * xa) <= abs(x1 - x2) &&
        abs((y1 + y2) - 2 * ya) <= abs(y1 - y2));
}

int main()
{
    int x1, y1, x2, y2, xa, ya, rc;
    char t;

    setbuf(stdout, NULL);
    printf("Segment and point:\n");

    rc = scanf("%d %d %d %d %d %d%c", &x1, &y1, &x2, &y2, &xa, &ya, &t);
    if (rc != 7 || rc == EOF || t != '\n')
    {
        return 1;
    }

    printf("%d\n", is_on_segment(x1, y1, x2, y2, xa, ya));

    return 0;
}
