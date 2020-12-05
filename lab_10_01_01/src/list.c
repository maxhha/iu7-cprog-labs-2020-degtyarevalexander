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

    while (p && cmp(p->data, data))
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

void front_back_split(node_t *head, node_t **back)
{
    if (!back)
        return;

    if (!head)
    {
        *back = NULL;
        return;
    }

    node_t *turtle = head;
    node_t *hare = head->next;

    while (hare)
    {
        hare = hare->next;

        if (!hare)
            break;

        turtle = turtle->next;
        hare = hare->next;
    }

    *back = turtle->next;
    turtle->next = NULL;
}

#define APPEND(head, tail, el) do { \
    if (tail) \
    { \
        tail = tail->next = el; \
    } \
    else \
    { \
        head = tail = el; \
    } \
} while (0)

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*cmp)(const void*, const void*))
{
    if (!head_a || !head_b || !cmp)
        return NULL;

    node_t *a = *head_a;
    node_t *b = *head_b;
    node_t *head = NULL, *tail = NULL;

    while (a && b)
    {
        node_t *next;

        if (cmp(a->data, b->data) < 0)
        {
            next = a;
            a = a->next;
        }
        else
        {
            next = b;
            b = b->next;
        }

        APPEND(head, tail, next);
    }

    while (a)
    {
        APPEND(head, tail, a);
        a = a->next;
    }

    while (b)
    {
        APPEND(head, tail, b);
        b = b->next;
    }

    if (tail)
        tail->next = NULL;

    *head_a = NULL;
    *head_b = NULL;

    return head;
}

node_t *sort(node_t *head, int (*cmp)(const void*, const void*))
{
    if (!head || !cmp)
        return NULL;

    if (!head->next)
        return head;

    node_t *back;
    front_back_split(head, &back);

    head = sort(head, cmp);
    back = sort(back, cmp);

    return sorted_merge(&head, &back, cmp);
}
