#include <stdio.h>
#include <math.h>

#define OK 0
#define INPUT_ERR 1

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

    setbuf(stdout, NULL);
    printf("Segment and point:\n");

    rc = scanf("%f %f %f %f %f %f", &x1, &y1, &x2, &y2, &xa, &ya);
    if (rc < 6 || rc == EOF || (x1 == x2 && y1 == y2))
    {
        printf("no no no\n");
        return INPUT_ERR;
    }

    printf("%d\n", is_on_segment(x1, y1, x2, y2, xa, ya));

    return OK;
}
