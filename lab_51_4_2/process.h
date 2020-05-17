#include <stdio.h>
#include <math.h>

#define OK 0
#define EINPUT -1
#define EZERODIV -2
#define EPS 1e-6
#define FEQUAL(a,b) (fabs((a) - (b)) < EPS)

int find_min_max_interval(FILE *f, double *start_val, double *end_val);
int get_mean_on_interval(FILE *f, double start_val, double end_val, double *mean);
