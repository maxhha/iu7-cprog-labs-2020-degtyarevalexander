#ifndef __LOG_H__
#define __LOG_H__

#define LOG_LEVEL 0x00
#include "macrologger.h"

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG_MATRIX(m) do {\
    for (size_t y = 0; y < (m)->height; y++) \
    { \
        PRINTFUNCTION(LOG_FMT "%d", LOG_ARGS(DEBUG_TAG), (m)->data[y * (m)->width]); \
        for (size_t x = 1; x < (m)->width; x++) \
            PRINTFUNCTION("\t%d", (m)->data[x + y * (m)->width]); \
        PRINTFUNCTION("%s", NEWLINE); \
    } \
} while(0)
#else
#define LOG_DEBUG_MATRIX(m)
#endif

#endif // __LOG_H__
