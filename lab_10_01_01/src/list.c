#include "../inc/list.h"

void free_list(node_t *head, void (*free_data)(void *))
{
    node_t *p = head;

    while (p)
    {
        free_data(p->data);
        node_t *t = p;
        p = p->next;
        free(t);
    }
}

void *pop_front(node_t **head)
{
    if (!head || !*head)
        return NULL;

    void *data = (*head)->data;
    node_t *next = (*head)->next;

    free(*head);
    *head = next;

    return data;
}
