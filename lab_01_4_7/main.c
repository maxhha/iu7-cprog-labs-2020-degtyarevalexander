#include <stdio.h>
#include <math.h>

float s_x(float x, float eps)
{
    float res = 0;
    float t = 1;
    long int n = 1;

    while (fabs(t) > eps)
    {
        res += t;

        t = -t / n * (n + 2) * x;

        n += 1;
    }

    return res;
}

int main()
{
    float x, eps;
    float fx, sx;
    float err;

    printf("x, eps:\n    ");

    if (scanf("%f %f", &x, &eps) == 2 && fabs(x) < 1 && eps > 0 && eps < 1)
    {
        sx = s_x(x, eps);
        fx = exp(-3 * log(1 + x));

        printf("\ns(x): %.6f \nf(x): %.6f\n", sx, fx);

        err = fabs(fx - sx);

        printf("\nAbsolute error: %.6f", err);
        printf("\nRelative error: %.6f\n", fabs(err / fx));

        return 0;
    }
    else
    {
        printf("no no no\n");
        return 1;
    }
}
