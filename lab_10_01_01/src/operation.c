#include "../inc/operation.h"

node_t *operation_first(node_t **in_list)
{
    transaction_t *tr = pop_front(in_list);

    if (!tr)
        return NULL;

    node_t *r = malloc(sizeof(node_t));

    if (!r)
    {
        free_transaction(tr);
        return NULL;
    }

    r->next = NULL;
    r->data = tr;
    return r;
}

int cmp_amount_is_greater(const void *a, const void *b)
{
    return ((transaction_t *) a)->amount > ((transaction_t *) b)->amount;
}

node_t *operation_find(node_t **in_list)
{
    node_t *head = NULL;
    node_t *tail = NULL;
    transaction_t *data = (*in_list)->data;

    node_t *p = find((*in_list)->next, data, cmp_amount_is_greater);

    while (p)
    {
        node_t *t = malloc(sizeof(node_t));

        if (!t)
        {
            free_list(head, (void (*)(void *)) free_transaction);
            return NULL;
        }

        t->data = copy_transaction(p->data);

        if (!t->data)
        {
            free(t);
            free_list(head, (void (*)(void *)) free_transaction);
            return NULL;
        }

        t->next = NULL;

        if (tail)
        {
            tail->next = t;
            tail = t;
        }
        else
        {
            head = tail = t;
        }

        p = find(p->next, data, cmp_amount_is_greater);
    }

    return head;
}

node_t *operation_reverse(node_t **in_list)
{
    node_t *head = reverse(*in_list);

    *in_list = NULL;

    return head;
}
