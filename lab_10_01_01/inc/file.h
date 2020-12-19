#ifndef __FILE_H__
#define __FILE_H__

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "transaction.h"
#include "log.h"

node_t *read_csv(char *filename);
void write_csv(char *filename, node_t *head);

#endif // __FILE_H__
