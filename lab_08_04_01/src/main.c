#include "../inc/main.h"

int main(void)
{
    LOG_DEBUG("read matrix A%s", "");

    matrix_t *a = scan_matrix();

    if (a == NULL)
    {
        LOG_ERROR("failed to scan matrix A%s", "");
        return EXIT_FAILURE;
    }

    LOG_DEBUG("matrix A = %p", (void *) a);
    LOG_DEBUG("read matrix B%s", "");

    matrix_t *b = scan_matrix();

    if (b == NULL)
    {
        LOG_ERROR("failed to scan matrix B%s", "");
        free_matrix(a);
        return EXIT_FAILURE;
    }

    LOG_DEBUG("matrix B = %p", (void *) b);
    LOG_DEBUG("read a_pwr b_pwr%s", "");

    int a_pwr, b_pwr;

    LOG_DEBUG("scan a and b powers%s", "");

    if (scanf("%d %d", &a_pwr, &b_pwr) != 2)
    {
        LOG_ERROR("invalid input for a_pwr or b_pwr%s", "");

        free_matrix(b);
        free_matrix(a);
        return EXIT_FAILURE;
    }

    LOG_DEBUG("a_pwr = %d, b_pwr = %d", a_pwr, b_pwr);

    if (a_pwr < 0 || b_pwr < 0)
    {
        LOG_ERROR("a_pwr or b_pwr is negative%s", "");

        free_matrix(b);
        free_matrix(a);
        return EXIT_FAILURE;
    }

    LOG_DEBUG("cut matrix A%s", "");

    matrix_t *a_cutted = cut_matrix(a);

    if (a_cutted == NULL)
    {
        LOG_ERROR("matrix A not cutted%s", "");

        free_matrix(b);
        return EXIT_FAILURE;
    }

    free_matrix(a);
    a = a_cutted;

    LOG_DEBUG("update matrix A = %p", (void *) a);
    LOG_DEBUG("cut matrix B%s", "");

    matrix_t *b_cutted = cut_matrix(b);

    if (b_cutted == NULL)
    {
        LOG_ERROR("matrix B not cutted%s", "");

        free_matrix(b);
        free_matrix(a_cutted);
        return EXIT_FAILURE;
    }

    free_matrix(b);
    b = b_cutted;

    LOG_DEBUG("update matrix B = %p", (void *) b);
    LOG_DEBUG("select matrix to grow%s", "");
    LOG_DEBUG("a->width = %lu, b->width = %lu", a->width, b->width);

    if (a->width < b->width)
    {
        LOG_DEBUG("grow matrix A%s", "");
        matrix_t *growed = grow_matrix(a, b->width);

        if (growed == NULL)
        {
            LOG_ERROR("grow failed%s", "");
            free_matrix(b);
            free_matrix(a);
            return EXIT_FAILURE;
        }

        free_matrix(a);
        a = growed;

        LOG_DEBUG("update matrix A = %p", (void *) a);
    }
    else if (a->width > b->width)
    {
        LOG_DEBUG("grow matrix B%s", "");
        matrix_t *growed = grow_matrix(b, a->width);

        if (growed == NULL)
        {
            LOG_ERROR("grow failed%s", "");
            free_matrix(b);
            free_matrix(a);
            return EXIT_FAILURE;
        }

        free_matrix(b);
        b = growed;

        LOG_DEBUG("update matrix B = %p", (void *) b);
    }
    else {
        LOG_DEBUG("grow matrixes are equal%s", "");
    }

    LOG_DEBUG("make power of A%s", "");

    matrix_t *a_in_power = get_matrix_power(a, a_pwr);

    if (a_in_power == NULL)
    {
        LOG_ERROR("get power of matrix A broken%s", "");
        free_matrix(b);
        free_matrix(a);
        return EXIT_FAILURE;
    }

    free_matrix(a);
    a = a_in_power;

    LOG_DEBUG("make power of B%s", "");

    matrix_t *b_in_power = get_matrix_power(b, b_pwr);

    if (b_in_power == NULL)
    {
        LOG_ERROR("get power of matrix A broken%s", "");
        free_matrix(b);
        free_matrix(a);
        return EXIT_FAILURE;
    }

    free_matrix(b);
    b = b_in_power;

    LOG_DEBUG("multiply matrix A @ B%s", "");

    matrix_t *result = multiply_matrix(a, b);

    if (result == NULL)
    {
        LOG_ERROR("multiplication is broken%s", "");
        free_matrix(b);
        free_matrix(a);
        return EXIT_FAILURE;
    }

    LOG_DEBUG("output result%s", "");

    print_matrix(result);

    LOG_DEBUG("free memory%s", "");

    free_matrix(result);
    free_matrix(b);
    free_matrix(a);

    return EXIT_SUCCESS;
}
