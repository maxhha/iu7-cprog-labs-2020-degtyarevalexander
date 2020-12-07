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

int cmp_power_by_base(const void *a, const void *b)
{
    int a_base = ((power_t *) a)->base;
    int b_base = ((power_t *) b)->base;

    return a_base > b_base ? -1 : a_base == b_base ? 0 : 1;
}

bool is_base_simple_in_power_list(node_t *head, int base)
{
    for (node_t *p = head; p && p->next; p = p->next)
    {
        if (base % ((power_t *) p->data)->base == 0)
            return false;
    }
    return true;
}

node_t *remove_zero_powers(node_t *head)
{
    for (node_t *p = head, *prev = NULL; p && p->next ; )
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

node_t *int_to_power_list(int x)
{
    node_t *head = create_power(1, 0);

    if (!head)
        return NULL;

    while (x > 1)
    {
        LOG_DEBUG("x = %d", x);

        int pwr = 0, base = head->next ? ((power_t *) head->data)->base : 2;

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

    return remove_zero_powers(head);
}

void print_power_list(node_t *head)
{
    if (head == NULL)
    {
        printf("(NO OUT, ERROR)\n");
        return;
    }

    node_t *p = head;
    power_t *power = (power_t *) p->data;

    while (power->base > 1)
    {
        printf("%d %d ", power->base, power->pwr);

        p = p->next;
        power = (power_t *) p->data;
    }

    printf("1\n");
}

node_t *multiply_power_lists(node_t **head_a, node_t **head_b)
{
    node_t *head = sorted_merge(head_a, head_b, cmp_power_by_base);

    for (node_t *p = head; p && p->next;)
    {
        power_t *power = (power_t *) p->data;
        power_t *next_power = (power_t *) p->next->data;

        LOG_DEBUG("base: %d; %d", power->base, next_power->base);
        if (power->base != next_power->base)
        {
            p = p->next;
            continue;
        }

        ((power_t *) p->data)->pwr += ((power_t *) p->next->data)->pwr;
        free(pop_front(&p->next));
    }

    return head;
}
