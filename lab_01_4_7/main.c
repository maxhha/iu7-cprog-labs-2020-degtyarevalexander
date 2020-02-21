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

int main(void)
{
    float x, eps;
    float fx, sx;
    float abs_err, rel_err;

    printf("x, eps:\n    ");

    if (scanf("%f %f", &x, &eps) == 2 && fabs(x) < 1 && eps > 0 && eps < 1)
    {
        sx = s_x(x, eps);
        fx = exp(-3 * log(1 + x));

        printf("\ns(x): %.6f \nf(x): %.6f\n", sx, fx);

        abs_err = fabs(fx - sx);
        rel_err = fabs(abs_err / fx);

        printf("\nAbsolute error: %.6f", abs_err);
        printf("\nRelative error: %.6f\n", rel_err);

        return 0;
    }
    else
    {
        printf("Ошибка при вводе данных\n");
        return 1;
    }
}
