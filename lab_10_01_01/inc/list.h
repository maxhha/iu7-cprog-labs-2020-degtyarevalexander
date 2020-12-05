#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

void free_list(node_t *head, void (*free_data)(void *));

void *pop_front(node_t **head);
node_t *find(node_t *head, const void *data,
    int (*comparator)(const void*, const void*));

#endif // __LIST_H__
