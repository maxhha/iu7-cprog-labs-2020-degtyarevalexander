#include <stdio.h>
#include <math.h>

double s_x(double x, double eps)
{
    double res = 0;
    double t = 1;
    long int n = 1;

    while (fabs(t) > eps)
    {
        res += t;

        t = -t / n * (n + 2) * x;

        n += 1;
    }

    return res + t;
}

int main(void)
{
    double x, eps;
    double fx, sx;
    double abs_err, rel_err;

    printf("Введите x и eps:\n    ");

    if (scanf("%lf %lf", &x, &eps) == 2 && fabs(x) < 1 && eps > 0)
    {
        sx = s_x(x, eps);
        fx = exp(-3 * log(1 + x));

        printf("\ns(x): %.6lf \nf(x): %.6lf\n", sx, fx);

        abs_err = fabs(fx - sx);
        rel_err = fabs(abs_err / fx);

        printf("\nAbsolute error: %.6lf", abs_err);
        printf("\nRelative error: %.6lf\n", rel_err);

        return 0;
    }
    else
    {
        printf("Ошибка при вводе данных\n");
        return 1;
    }
}
