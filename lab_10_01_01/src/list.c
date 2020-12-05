#include "../inc/list.h"

void free_list(node_t *head, void (*free_data)(void *))
{
    node_t *p = head;

    while (p)
    {
        if (free_data)
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

node_t *find(node_t *head, const void *data, int (*cmp)(const void *, const void *))
{
    if (!cmp)
        return NULL;

    node_t *p = head;

    while (p && !cmp(p->data, data))
    {
        p = p->next;
    }

    return p;
}

node_t *reverse(node_t *head)
{
    node_t *p = head, *pp = NULL;

    while (p)
    {
        node_t *n = p->next;
        p->next = pp;
        pp = p;
        p = n;
    }

    return pp;
}
