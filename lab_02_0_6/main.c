#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define MICROSEC_PER_SEC 1000000LL

#define MAX_ARRAY_SIZE 10000
#define OK 0
#define INPUT_ERR 1

int scanf_array(int *a, int *const len)
{
    printf("Enter array length:\n");
    int rc = scanf("%d", len);

    if (rc != 1 || *len <= 0 || *len > MAX_ARRAY_SIZE)
    {
        return INPUT_ERR;
    }

    printf("Enter array elements:\n");

    for (int i = 0; i < *len; i++)
    {
        rc = scanf("%d", a + i);

        if (rc != 1 || rc == EOF)
        {
            return INPUT_ERR;
        }
    }
    return OK;
}

/**
 * Использование операции индексации a[i]
 */
int process_1(const int *a, const int n)
{
    int f = 0;
    int l = n - 1;
    int max = a[f] + a[l];
    int x;

    while (f <= l)
    {
        x = a[f] + a[l];
        if (x > max)
            max = x;
        f++;
        l--;
    }
    return max;
}

/**
 * Формальная замена операции индексации на выражение *(a + i)
 */
int process_2(const int *a, const int n)
{
    int f = 0;
    int l = n - 1;
    int max = *(a + f) + *(a + l);
    int x;

    while (f <= l)
    {
        x = *(a + f) + *(a + l);
        if (x > max)
            max = x;
        f++;
        l--;
    }
    return max;
}

/**
 * Использование указателей для работы с массивом.
 */
int process_3(const int *a, const int n)
{
    const int *f = a;
    const int *l = a + n - 1;
    int max = *f + *l;
    int x;

    while (f <= l)
    {
        x = *f + *l;
        if (x > max)
            max = x;
        f++;
        l--;
    }
    return max;
}

void print_header(void)
{
    printf("| Количество повторов (N) ");
    printf("| Размер массива ");
    printf("| a[i] ");
    printf("| *(a + i) ");
    printf("| Работа с указателями ");
    printf("|\n");

    printf("| ---:| ---:| ---:| ---:| ---:|\n");
}

double time_function(int (*const process)(const int*, const int), const int *a, const int n, const int repeats)
{
    double sum = 0;
    double min_time = INFINITY;
    double max_time = -INFINITY;
    double current_time;

    clock_t start, stop;

    for (int i = 0; i < repeats + 2; i++)
    {
        start = clock();
        process(a, n);
        stop = clock();

        current_time = (double) (stop - start) / CLOCKS_PER_SEC * MICROSEC_PER_SEC;

        sum += current_time;

        min_time = MIN(min_time, current_time);
        max_time = MAX(max_time, current_time);
    }

    return (sum - min_time - max_time) / repeats;
}

int main(void)
{
    int a[MAX_ARRAY_SIZE];
    int n, rc, repeats, header;

    setbuf(stdout, NULL);

    printf("Show header?(1/0):\n");
    rc = scanf("%d", &header);

    if (rc != 1 || rc == EOF)
    {
        printf("Invalid header.\n");
        return INPUT_ERR;
    }

    printf("Enter repeats:\n");
    rc = scanf("%d", &repeats);

    if (rc != 1 || rc == EOF || repeats <= 0)
    {
        printf("Invalid number of repeats.\n");
        return INPUT_ERR;
    }

    rc = scanf_array(a, &n);

    if (rc != OK)
    {
        printf("Invalid array input.\n");
        return INPUT_ERR;
    }

    if (header)
    {
        print_header();
    }

    printf("| %d | %d | ", repeats, n);

    // Измерение использования операции индексации
    printf("%0.6lf µs | ", time_function(process_1, a, n, repeats));

    // Измерение формальной замены операции индексации на выражение *(a + i)
    printf("%0.6lf µs | ", time_function(process_2, a, n, repeats));

    // Измерение использования указателей для работы с массивом.
    printf("%0.6lf µs | ", time_function(process_3, a, n, repeats));

    printf("\n");

    return OK;
}
