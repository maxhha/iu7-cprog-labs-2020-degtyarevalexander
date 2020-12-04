#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

typedef struct {
    char *date;
    int amount;
    char *message;
} transaction_t;

#define STRING_DELIMETRS

transaction_t *create_transaction_from_line(char *str);
void free_transaction(transaction_t *);

#endif // __TRANSACTION_H__
