#include "../inc/main.h"
#include <stdarg.h>

int read_matrixes(matrix_t **a, matrix_t **b)
{
    LOG_DEBUG("read matrix A%s", "");

    *a = scan_matrix();

    if (*a == NULL)
    {
        LOG_ERROR("failed to scan matrix A%s", "");
        return EXIT_FAILURE;
    }

    LOG_DEBUG("read matrix B%s", "");

    *b = scan_matrix();

    if (*b == NULL)
    {
        LOG_ERROR("failed to scan matrix B%s", "");
        free_matrix(*a);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int read_powers(int *a_pwr, int *b_pwr)
{
    LOG_DEBUG("read a_pwr b_pwr%s", "");

    LOG_DEBUG("scan a and b powers%s", "");

    if (scanf("%d %d", a_pwr, b_pwr) != 2)
    {
        LOG_ERROR("invalid input for a_pwr or b_pwr%s", "");

        return EXIT_FAILURE;
    }

    LOG_DEBUG("a_pwr = %d, b_pwr = %d", *a_pwr, *b_pwr);

    if (*a_pwr < 0 || *b_pwr < 0)
    {
        LOG_ERROR("a_pwr or b_pwr is negative%s", "");

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int grow_matrixes(matrix_t **a, matrix_t **b)
{
    LOG_DEBUG("select matrix to grow%s", "");
    LOG_DEBUG("a->width = %lu, b->width = %lu", (*a)->width, (*b)->width);

    matrix_t **small_m, **big_m;

    if ((*a)->width < (*b)->width)
    {
        LOG_DEBUG("grow matrix A%s", "");
        small_m = a;
        big_m = b;
    }
    else if ((*a)->width > (*b)->width)
    {
        LOG_DEBUG("grow matrix B%s", "");
        small_m = b;
        big_m = a;
    }
    else
    {
        LOG_DEBUG("grow matrixes are equal%s", "");
        return EXIT_SUCCESS;
    }

    matrix_t *growed_m = grow_matrix(*small_m, (*big_m)->width);

    if (growed_m == NULL)
    {
        LOG_ERROR("grow failed%s", "");
        return EXIT_FAILURE;
    }

    free_matrix(*small_m);
    *small_m = growed_m;

    return EXIT_SUCCESS;
}

int make_powers(matrix_t **a, matrix_t **b, int a_pwr, int b_pwr)
{
    LOG_DEBUG("make power of A%s", "");

    matrix_t *a_in_power = get_matrix_power(*a, a_pwr);

    if (a_in_power == NULL)
    {
        LOG_ERROR("get power of matrix A broken%s", "");
        return EXIT_FAILURE;
    }

    free_matrix(*a);
    *a = a_in_power;

    LOG_DEBUG("make power of B%s", "");

    matrix_t *b_in_power = get_matrix_power(*b, b_pwr);

    if (b_in_power == NULL)
    {
        LOG_ERROR("get power of matrix A broken%s", "");
        return EXIT_FAILURE;
    }

    free_matrix(*b);
    *b = b_in_power;

    return EXIT_SUCCESS;
}

int main(void)
{
    matrix_t *a, *b, *result;
    int a_pwr, b_pwr;

    if (read_matrixes(&a, &b) != EXIT_SUCCESS)
    {
        LOG_ERROR("fail read matrixes%s", "");
        return EXIT_FAILURE;
    }

    if (read_powers(&a_pwr, &b_pwr) != EXIT_SUCCESS)
    {
        LOG_ERROR("fail read powers%s", "");
        free_matrixes(2, a, b);
        return EXIT_FAILURE;
    }

    if (cut_matrixes(2, a, b) != 2)
    {
        LOG_ERROR("matrixes not cutted%s", "");
        free_matrixes(2, a, b);
        return EXIT_FAILURE;
    }

    if (grow_matrixes(&a, &b) != EXIT_SUCCESS)
    {
        LOG_ERROR("fail grow matrixes%s", "");
        free_matrixes(2, a, b);
        return EXIT_FAILURE;
    }

    if (make_powers(&a, &b, a_pwr, b_pwr) != EXIT_SUCCESS)
    {
        LOG_ERROR("fail grow matrixes%s", "");
        free_matrixes(2, a, b);
        return EXIT_FAILURE;
    }

    LOG_DEBUG("multiply matrix A @ B%s", "");

    if ((result = multiply_matrix(a, b)) == NULL)
    {
        LOG_ERROR("multiplication is broken%s", "");
        free_matrixes(2, a, b);
        return EXIT_FAILURE;
    }

    LOG_DEBUG("output result%s", "");

    print_matrix(result);

    LOG_DEBUG("free memory%s", "");

    free_matrixes(3, result, a, b);

    return EXIT_SUCCESS;
}
