#include <stdio.h>

#define OK 0

int main()
{
    float v1, t1, v2, t2, v, t;

    setbuf(stdout, NULL);
    printf("Enter two pairs of volume and temperature:\n");

    scanf("%f %f %f %f", &v1, &t1, &v2, &t2);

    v = v1 + v2;
    t = (v1 * t1 + v2 * t2) / v;

    printf("Volume: %f\nTemperature: %f\n", v, t);

    return OK;
}
