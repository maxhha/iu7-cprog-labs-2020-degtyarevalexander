#include <stdio.h>

int main()
{
    float v1, t1, v2, t2, v, t;

    setbuf(stdout, NULL);
    printf("Input:\n");

    scanf("%f %f %f %f", &v1, &t1, &v2, &t2);

    v = v1 + v2;
    t = (v1 * t1 + v2 * t2) / v;

    printf("%f %f\n", v, t);

    return 0;
}
