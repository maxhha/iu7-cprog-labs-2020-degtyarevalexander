#include <stdio.h>
#include <math.h>

#define OK 0
#define INPUT_ERR 1

double calc_func_as_series(double x, double eps)
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

    return res;
}

int main()
{
    double x, eps;
    double f, s;
    double err;

    printf("x, eps:\n");

    if (scanf("%lf %lf", &x, &eps) != 2 || fabs(x) >= 1 || eps <= 0 || eps >= 1)
    {
        printf("no no no\n");
        return INPUT_ERR;
    }
    s = calc_func_as_series(x, eps);
    f = exp(-3 * log(1 + x));
    err = fabs(f - s);

    printf("s(x): %.6lf\nf(x): %.6lf\n", s, f);
    printf("Absolute error: %.6lf\n", err);
    printf("Relative error: %.6lf\n", fabs(err / f));

    return OK;
}
