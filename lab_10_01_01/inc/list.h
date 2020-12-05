#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

#define APPEND(head, tail, el) do { \
    if (tail) \
        tail = tail->next = el; \
    else \
        head = tail = el; \
} while (0)

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

void free_list(node_t *head, void (*free_data)(void *));

void *pop_front(node_t **head);
node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*));
node_t *reverse(node_t *head);
node_t *sort(node_t *head, int (*comparator)(const void*, const void*));

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*cmp)(const void*, const void*));
void front_back_split(node_t *head, node_t **back);

#endif // __LIST_H__
