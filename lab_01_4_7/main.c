#include <stdio.h>
#include <math.h>

#define OK 0
#define INPUT_ERR 1

float my_f(float x, float eps)
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
    float fx, my_fx;
    float err;

    printf("x, eps:\n");

    if (scanf("%f %f", &x, &eps) == 2 && fabs(x) < 1 && eps > 0 && eps < 1)
    {
        my_fx = my_f(x, eps);
        fx = exp(-3 * log(1 + x));
        err = fabs(fx - my_fx);

        printf("s(x): %.6f\nf(x): %.6f\n", my_fx, fx);
        printf("Absolute error: %.6f\n", err);
        printf("Relative error: %.6f\n", fabs(err / fx));

        return OK;
    }
    else
    {
        printf("no no no\n");
        return INPUT_ERR;
    }
}
