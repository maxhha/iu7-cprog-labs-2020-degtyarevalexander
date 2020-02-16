#include <stdio.h>
#include <math.h>

int is_on_segment(float x1, float y1, float x2, float y2, float xa, float ya)
{
    return ((y2 - y1) * (x2 - xa) == (y2 - ya) * (x2 - x1) &&
        fabs((x1 + x2) - 2 * xa) <= fabs(x1 - x2) &&
        fabs((y1 + y2) - 2 * ya) <= fabs(y1 - y2));
}

int main()
{
    float x1, y1, x2, y2, xa, ya;
    int rc;
    char t;

    setbuf(stdout, NULL);
    printf("Segment and point:\n");

    rc = scanf("%f %f %f %f %f %f%c", &x1, &y1, &x2, &y2, &xa, &ya, &t);
    if (rc != 7 || rc == EOF || t != '\n')
    {
        return 1;
    }

    printf("%d\n", is_on_segment(x1, y1, x2, y2, xa, ya));

    return 0;
}
