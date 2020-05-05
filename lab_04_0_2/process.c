#include <string.h>
#include "process.h"

int count_strstr(const char *where, const char *what)
{
    int c = 0;
    where = strstr(where, what);

    while (where != NULL)
    {
        c++;
        where = strstr(where + 1, what);
    }

    return c;
}

int count_words(char words[][WORD_STR_MAX_SIZE + 1], int words_n, int *counts)
{
    for (int i = 0; i < words_n; i++)
    {
        *counts = 0;
        for (int j = 0; j < words_n; j++)
        {
            *counts += count_strstr(words[j], words[i]);
        }
        counts++;
    }
    return words_n;
}
