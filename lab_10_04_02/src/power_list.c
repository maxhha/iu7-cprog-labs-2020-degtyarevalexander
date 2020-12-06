#include "../inc/power_list.h"

node_t *create_power(int base, int pwr)
{
    power_t *p = malloc(sizeof(power_t));

    if (!p)
        return NULL;

    p->base = base;
    p->pwr = pwr;

    node_t *n = malloc(sizeof(node_t));

    if (!n)
    {
        free(p);
        return NULL;
    }

    n->next = NULL;
    n->data = p;

    return n;
}

// int cmp_power_by_base(const void *a, const void *b)
// {
//     int a_base = ((power_t *) a)->base;
//     int b_base = ((power_t *) b)->base;
//
//     return a_base < b_base ? -1 : a_base == b_base ? 0 : 1;
// }

bool is_base_simple_in_power_list(node_t *head, int base)
{
    for (node_t *p = head; p; p = p->next)
    {
        if (base % ((power_t *) p->data)->base == 0)
            return false;
    }
    return true;
}

node_t *int_to_power_list(int x)
{
    node_t *head = NULL;

    while (x > 1)
    {
        LOG_DEBUG("x = %d", x);

        int pwr = 0, base = head ? ((power_t *) head->data)->base : 2;

        while (!is_base_simple_in_power_list(head, base))
            base++;

        LOG_DEBUG("base = %d", base);

        while (x % base == 0)
        {
            x /= base;
            pwr++;
        }

        LOG_DEBUG("pwr = %d", pwr);

        node_t *p = create_power(base, pwr);

        if (!p)
        {
            free_list(head, free);
            return NULL;
        }

        p->next = head;
        head = p;
    }

    for (node_t *p = head, *prev = NULL; p; )
    {
        if (((power_t *) p->data)->pwr != 0)
        {
            prev = p;
            p = p->next;
            continue;
        }

        LOG_DEBUG("remove base %d", ((power_t *) p->data)->base);

        if (prev)
        {
            free(pop_front(&prev->next));
            p = prev->next;
        }
        else
        {
            free(pop_front(&head));
            p = head;
        }
    }

    return head;
}

void print_power_list(node_t *head)
{
    for (node_t *p = head; p; p = p->next)
    {
        power_t *power = (power_t *) p->data;
        printf("%d %d ", power->base, power->pwr);
    }

    printf("1\n");
}
