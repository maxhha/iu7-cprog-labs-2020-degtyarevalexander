#include <stdio.h>
#include <stdlib.h>
#include "sizes.h"
#include "input.h"
#include "process.h"
#include "output.h"

int main(void)
{
    char words[MAX_WORDS][WORD_STR_MAX_SIZE + 1];
    int counts[MAX_WORDS];
    int words_n;

    printf("Enter a string:\n");
    words_n = scan_words(words);

    if (words_n == INPUT_ERR)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    count_words(words, words_n, counts);

    printf("Result:\n");
    print_words_counts((const char(*)[WORD_STR_MAX_SIZE + 1]) words, counts, words_n);

    return EXIT_SUCCESS;
}
