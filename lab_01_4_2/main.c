#include <stdio.h>
#define __USE_MISC 1
#include <math.h>

int main()
{
    setbuf(stdout, NULL);
    printf("Enter a b alpha:\n");

    int a, b, alpha;
    scanf("%d %d %d", &a, &b, &alpha);

    double h = fabs((b - a) / 2.0 * tan(alpha * M_PI / 180.0));

    printf("Square is %0.2f\n", h*(a+b)/2.0);
    return 0;
}
