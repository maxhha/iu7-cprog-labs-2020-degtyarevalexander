#include <stdio.h>
#include <string.h>
#include "output.h"

void print_words_counts(const char words[][WORD_STR_MAX_SIZE + 1], const int *counts, int words_n)
{
    int j;
    for (int i = 0; i < words_n; i++)
    {
        for (j = 0; j < i; j++)
            if (strcmp(words[i], words[j]) == 0)
                break;

        if (j == i)
            printf("%s %d\n", words[i], counts[i]);
    }
}
