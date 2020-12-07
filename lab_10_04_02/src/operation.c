#include "../inc/operation.h"

int scanf_power_lists(int n, ...)
{
    va_list args;
    va_start(args, n);

    int i = 0;

    while (i < n)
    {
        node_t **head = va_arg(args, node_t **);
        int x;

        if (scanf("%d", &x) != 1 || x < 1)
        {
            LOG_ERROR("fail read number%s", "");
            break;
        }

        LOG_DEBUG("x = %d", x);

        *head = int_to_power_list(x);

        if (!*head)
        {
            LOG_ERROR("fail to create power list%s", "");
            break;
        }

        i++;
    }

    va_end(args);

    return i;
}

int perform_operation_out(void)
{
    node_t *a;

    if (scanf_power_lists(1, &a) != 1)
        return EXIT_FAILURE;

    print_power_list(a);

    free_list(a, free);

    return EXIT_SUCCESS;
}

int perform_operation_mul(void)
{
    node_t *a = NULL, *b = NULL;

    if (scanf_power_lists(2, &a, &b) != 2)
    {
        if (a)
            free_list(a, free);
        return EXIT_FAILURE;
    }

    node_t *result = multiply_power_lists(&a, &b);
    print_power_list(result);

    free_list(result, free);

    return EXIT_SUCCESS;
}

int perform_operation_sqr(void)
{
    node_t *a = NULL, *b = NULL;

    if (scanf_power_lists(1, &a) != 1)
        return EXIT_FAILURE;

    b = copy_power_list(a);

    if (!b)
    {
        free_list(a, free);
        return EXIT_FAILURE;
    }

    node_t *result = multiply_power_lists(&a, &b);
    print_power_list(result);

    free_list(result, free);

    return EXIT_SUCCESS;
}

int perform_operation_div(void)
{
    node_t *a = NULL, *b = NULL;

    if (scanf_power_lists(2, &a, &b) != 2)
    {
        if (a)
            free_list(a, free);
        return EXIT_FAILURE;
    }

    node_t *result = divide_power_lists(&a, &b);
    print_power_list(result);

    free_list(result, free);

    return EXIT_SUCCESS;
}
