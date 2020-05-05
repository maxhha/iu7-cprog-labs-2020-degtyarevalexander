#include <stdio.h>
#include <string.h>
#include "output.h"

void print_words_counts(const char words[][WORD_STR_MAX_SIZE + 1], const int *counts, int words_n)
{
    for (int i = 0; i < words_n; i++)
    {
        printf("%s %d\n", words[i], counts[i]);
    }
}
