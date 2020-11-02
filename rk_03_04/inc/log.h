#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>

// #define DEBUG

#ifdef DEBUG
#define LOG_DEBUG(...) \
    fprintf(stderr, __VA_ARGS__);
#else
#define LOG_DEBUG(...) \

#endif // DEBUG

#ifdef DEBUG
#define LOG_MATRIX(m) do { \
    for (int y = 0; y < (m)->height; y++) { \
        for (int x = 0; x < (m)->width; x++) { \
            LOG_DEBUG("%2d ", (m)->data[x + y * (m)->width]); \
        } \
        LOG_DEBUG("\n"); \
    } \
} while (0)
#else
#define LOG_MATRIX(m) \

#endif // DEBUG

#endif // __LOG_H__
