#ifndef __OPERATION_H__
#define __OPERATION_H__

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "power_list.h"

int perform_operation_out(void);
int perform_operation_mul(void);
int perform_operation_sqr(void);
int perform_operation_div(void);

#endif // __OPERATION_H__
