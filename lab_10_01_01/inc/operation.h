#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <stdlib.h>
#include <stdio.h>
#include "log.h"
#include "list.h"
#include "transaction.h"

node_t *operation_first(node_t **in_list);
node_t *operation_find(node_t **in_list);
node_t *operation_reverse(node_t **in_list);
node_t *operation_sort_by_date(node_t **in_list);

#endif // __OPERATION_H__
