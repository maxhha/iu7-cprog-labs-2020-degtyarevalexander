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
            break;

        *head = int_to_power_list(x);

        if (!*head)
            break;

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
    return EXIT_FAILURE;
}

int perform_operation_sqr(void)
{
    return EXIT_FAILURE;
}

int perform_operation_div(void)
{
    return EXIT_FAILURE;
}
