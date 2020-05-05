#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../lab_04_0_2/sizes.h"
#include "../lab_04_0_2/input.h"

void magic_process_word(char *word)
{
    char letter = *(word++);
    char *dest = word;
    while (*word != '\0')
    {
        if (*word == letter)
        {
            word++;
        }
        else
        {
            *(dest++) = *(word++);
        }
    }
    *dest = '\0';
}

char* strcat_reverse(char *dest, char *what)
{
    int word_len = strlen(what);
    char *p = strrchr(dest, '\0');
    char *p_new = p + word_len;

    while (p >= dest)
    {
        *(p_new--) = *(p--);
    }

    memcpy(dest, what, word_len);
    return dest;
}

void magic_process(char *dest, char words[][WORD_STR_MAX_SIZE + 1], int n_words)
{
    *dest = '\0';
    char (*last_word)[WORD_STR_MAX_SIZE + 1] = words + n_words - 1;
    bool first = true;

    for(char (*word)[WORD_STR_MAX_SIZE + 1] = words; word < last_word; word++)
    {
        if (strcmp(*last_word, *word) == 0)
        {
            continue;
        }

        magic_process_word(*word);

        if (!first)
        {
            strcat_reverse(dest, " ");
        }
        first = false;

        strcat_reverse(dest, *word);
    }
}

int main(void)
{
    char s[STR_MAX_SIZE];
    char words[MAX_WORDS][WORD_STR_MAX_SIZE + 1];
    int words_n;

    printf("Enter a string:\n");
    words_n = scan_words(words);

    if (words_n == INPUT_ERR)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    magic_process(s, words, words_n);

    if (strlen(s) == 0)
    {
        fprintf(stderr, "Output string is empty\n");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", s);

    return EXIT_SUCCESS;
}
