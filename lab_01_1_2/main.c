#include <stdio.h>

# define M_PI 3.14159265358979323846

double sin(double x)
{
    double s = x, p = x;
    for(int i = 2; i <= 20; i+=2)
    {
        p = -p*x/i*x/(i+1);
        s += p;
    }
    return s;
}

int main()
{
    int a, b, alpha;
    double angle, h;

    setbuf(stdout, NULL);
    printf("Enter a b alpha:\n");

    scanf("%d %d %d", &a, &b, &alpha);

    angle = alpha * M_PI / 180.0;
    h = (b - a) / 2.0 * sin(angle) / sin(angle + M_PI/2.0);

    if (h < 0)
    {
        h = -h;
    }

    printf("Square is %d\n", (int) (h*(a+b)/2.0));
    return 0;
}

