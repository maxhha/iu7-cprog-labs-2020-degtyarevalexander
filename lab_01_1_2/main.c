#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define OK 0

int main()
{
    float a, b, alpha, h;

    setbuf(stdout, NULL);
    printf("Enter a b alpha:\n");

    scanf("%f %f %f", &a, &b, &alpha);

    h = (b - a) / 2.0 * tan(alpha * M_PI / 180.0);

    if (h < 0)
    {
        h = -h;
    }

    printf("Square is %lf\n", (h * (a + b) / 2.0));
    return OK;
}
