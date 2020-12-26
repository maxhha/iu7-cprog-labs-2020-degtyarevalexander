#ifndef __MY_SNPRINTF_H__
#define __MY_SNPRINTF_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "log.h"

int my_snprintf (char *s, size_t maxlen, const char *format, ...);

#endif // __MY_SNPRINTF_H__
