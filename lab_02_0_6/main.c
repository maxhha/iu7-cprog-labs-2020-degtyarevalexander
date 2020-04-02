#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#define MAX_ARRAY_SIZE 10000
#define OK 0
#define INPUT_ERR 1

int scanf_array(int *a, int *len)
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

// использование операции индексации a[i]
int process_1(int *a, int n)
{
    int l = 0;
    int r = n - 1;
    int max = a[l] + a[r];
    while (l <= r)
    {
        int x = a[l] + a[r];
        if (x > max)
            max = x;
        l++;
        r--;
    }
    return max;
}

// формальная замена операции индексации на выражение *(a + i)
int process_2(int *a, int n)
{
    int l = 0;
    int r = n - 1;
    int max = *(a + l) + *(a + r);
    while (l <= r)
    {
        int x = *(a + l) + *(a + r);
        if (x > max)
            max = x;
        l++;
        r--;
    }
    return max;
}

// использование указателей для работы с массивом.
int process_3(int *a, int n)
{
    int *l = a;
    int *r = a + n - 1;
    int max = *l + *r;
    while (l <= r)
    {
        int x = *l + *r;
        if (x > max)
            max = x;
        l++;
        r--;
    }
    return max;
}

int main(void)
{
    int a[MAX_ARRAY_SIZE];
    int n, rc, repeats, header;

    struct timeval tv_start, tv_stop;
    double sum, min_time, max_time, current_time;

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
        printf("| Количество повторов (N) | Размер массива | a[i] | *(a + i) | Работа с указателями |\n");
        printf("| ---:| ---:| ---:| ---:| ---:|\n");
    }

    printf("| %d | %d | ", repeats, n);

    // Измерение использования операции индексации

    sum = 0;
    min_time = INFINITY;
    max_time = -INFINITY;

    for (int i = 0; i < repeats + 2; i++)
    {
        gettimeofday(&tv_start, NULL);
        process_1(a, n);
        gettimeofday(&tv_stop, NULL);

        current_time = (
            (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL
            + (tv_stop.tv_usec - tv_start.tv_usec)
        );

        sum += current_time;

        if (current_time < min_time)
            min_time = current_time;

        if (current_time > max_time)
            max_time = current_time;
    }

    printf("%0.6lf µs | ", (sum - min_time - max_time) / repeats);

    // Измерение формальной замены операции индексации на выражение *(a + i)

    sum = 0;
    min_time = INFINITY;
    max_time = -INFINITY;

    for (int i = 0; i < repeats + 2; i++)
    {
        gettimeofday(&tv_start, NULL);
        process_2(a, n);
        gettimeofday(&tv_stop, NULL);

        current_time = (
            (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL
            + (tv_stop.tv_usec - tv_start.tv_usec)
        );

        sum += current_time;

        if (current_time < min_time)
            min_time = current_time;

        if (current_time > max_time)
            max_time = current_time;
    }

    printf("%0.6lf µs | ", (sum - min_time - max_time) / repeats);

    // Измерение использования указателей для работы с массивом.

    sum = 0;
    min_time = INFINITY;
    max_time = -INFINITY;

    for (int i = 0; i < repeats + 2; i++)
    {
        gettimeofday(&tv_start, NULL);
        process_3(a, n);
        gettimeofday(&tv_stop, NULL);

        sum += current_time;

        if (current_time < min_time)
            min_time = current_time;

        if (current_time > max_time)
            max_time = current_time;
    }

    printf("%0.6lf µs | ", (sum - min_time - max_time) / repeats);

    printf("\n");

    return OK;
}
