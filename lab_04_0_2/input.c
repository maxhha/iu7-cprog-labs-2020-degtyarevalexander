#include <stdio.h>
#include "input.h"

int is_word_delimiter(char c)
{
    return (c == ' '
        || c == ','
        || c == ';'
        || c == ':'
        || c == '-'
        || c == '.'
        || c == '!'
        || c == '?'
    );
}

int scan_words(char words[][WORD_STR_MAX_SIZE + 1])
{
    char c;
    char *word = words[0];
    int word_len = 0;
    int n = 0;

    for (int i = 0; i <= STR_MAX_SIZE && word_len <= WORD_STR_MAX_SIZE; i++)
    {
        c = getchar();

        if (c == '\n' || c == EOF)
        {
            if (word_len == 0)
            {
                break;
            }
            n++;
            *word = '\0';
            break;
        }

        if (!is_word_delimiter(c))
        {
            word_len++;
            *(word++) = c;
        }
        else if (word_len > 0)
        {
            word_len = 0;
            *word = '\0';
            word = words[++n];
        }
    }

    if ((c == '\n' || c == EOF) && n > 0)
    {
        return n;
    }

    return INPUT_ERR;
}
