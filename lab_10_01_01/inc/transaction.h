#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

typedef struct
{
    char *date;
    int amount;
    char *message;
} transaction_t;

transaction_t *create_transaction_from_line(char *str);
transaction_t *copy_transaction(transaction_t *tr);
void free_transaction(transaction_t *);

#endif // __TRANSACTION_H__
