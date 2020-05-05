#include <string.h>
#include "process.h"

void count_words(char words[][WORD_STR_MAX_SIZE + 1], int words_n, int *counts)
{
    for (int i = 0; i < words_n; i++)
    {
        *counts = 0;
        for (int j = 0; j < words_n; j++)
        {
            *counts += strcmp(words[j], words[i]) == 0;
        }
        counts++;
    }
}
