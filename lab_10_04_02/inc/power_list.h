#ifndef __POWER_LIST_H__
#define __POWER_LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "log.h"
#include "list.h"

typedef struct
{
    int base;
    int pwr;
} power_t;

node_t *int_to_power_list(int x);
node_t *multiply_power_lists(node_t **head_a, node_t **head_b);
void print_power_list(node_t *head);

#endif // __POWER_LIST_H__
