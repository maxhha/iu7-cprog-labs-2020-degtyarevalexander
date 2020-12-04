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
