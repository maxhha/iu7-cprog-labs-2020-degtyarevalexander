#include <stdio.h>
#include <math.h>

#define OK 0
#define INPUT_ERR 1
#define EPSILON 1e-2

int fequal(float a, float b)
{
    return fabs(a - b) < EPSILON;
}

int is_on_segment(float x1, float y1, float x2, float y2, float xa, float ya)
{
    float dx1 = x1 - xa, dy1 = y1 - ya;
    float dx2 = x2 - xa, dy2 = y2 - ya;
    return (dx1 * dx2 + dy1 * dy2 <= EPSILON) && fabs(dx1 * dy2 - dx2 * dy1) <= EPSILON;
}

int main()
{
    float x1, y1, x2, y2, xa, ya;
    int rc;

    setbuf(stdout, NULL);
    printf("Segment and point:\n");

    rc = scanf("%f %f %f %f %f %f", &x1, &y1, &x2, &y2, &xa, &ya);
    if (rc != 6 || rc == EOF || (fequal(x1, x2) && fequal(y1, y2)))
    {
        printf("no no no\n");
        return INPUT_ERR;
    }

    printf("%d\n", is_on_segment(x1, y1, x2, y2, xa, ya));

    return OK;
}
