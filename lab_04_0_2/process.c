#include <string.h>
#include "process.h"

char *my_strstr(const char *where, const char *what)
{
    const char *i, *j;

    for (; *where != '\0'; where++)
    {
        i = where;
        j = what;
        while (*i == *j && *j != '\0')
        {
            i++;
            j++;
        }
        if (*j == '\0')
        {
            return (char *) where;
        }
    }
    return NULL;
}

int count_strstr(const char *where, const char *what)
{
    int c = 0;
    where = my_strstr(where, what);

    while (where != NULL)
    {
        c++;
        where = my_strstr(where + 1, what);
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
