#include <string.h>
#include "process.h"

int count_words(char words[][WORD_STR_MAX_SIZE + 1], int words_n, int *counts)
{
    int n = 0;
    int j;

    for (int i = 0; i < words_n; i++)
    {
        for (j = 0; j < i; j++)
            if (strcmp(words[i], words[j]) == 0)
                break;

        if (j < i)
        {
            counts[j] += 1;
            continue;
        }

        if (n != i)
            memcpy(words[n], words[i], WORD_STR_MAX_SIZE + 1);

        counts[n] = 1;
        n++;
    }
    return n;
}
