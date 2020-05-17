#include <stdio.h>
#include <stdbool.h>
#include "process.h"

int find_min_max_interval(FILE *f, double *start_val, double *end_val)
{
    double x, min, max;;
    bool max_is_last = true;

    if (fscanf(f, "%lf %lf", &min, &max) != 2)
    {
        return EINPUT;
    }

    if (min > max)
    {
        max_is_last = false;
        x = min;
        min = max;
        max = x;
    }

    while (fscanf(f, "%lf", &x) == 1)
    {
        if (x > max)
        {
            max = x;
            max_is_last = true;
        }
        if (x < min)
        {
            min = x;
            max_is_last = false;
        }
    }

    if (max_is_last)
    {
        *start_val = min;
        *end_val = max;
    }
    else
    {
        *start_val = max;
        *end_val = min;
    }

    return OK;
}

int get_mean_on_interval(FILE *f, double start_val, double end_val, double *mean)
{
    double x, sum = 0;
    int n = 0;

    while (fscanf(f, "%lf", &x) == 1 && !FEQUAL(x, start_val))
    {
    }

    if (!FEQUAL(x, start_val))
    {
        return EINPUT;
    }

    while (fscanf(f, "%lf", &x) == 1 && !FEQUAL(x, end_val))
    {
        sum += x;
        n++;
    }

    if (!FEQUAL(x, end_val))
    {
        return EINPUT;
    }

    if (n == 0)
    {
        return EZERODIV;
    }
    *mean = sum / n;

    return OK;
}
