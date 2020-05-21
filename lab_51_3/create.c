#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

void generate_file(char *filename, int n)
{
    FILE *f = fopen(filename, "wb");
    NUMBER_TYPE x;
    for (int i = 0; i < n; i++)
    {
        x = rand();
        fwrite(&x, sizeof(NUMBER_TYPE), 1, f);
    }
    fclose(f);
}

int main_create(int argc, char **argv)
{
    if (argc == 0)
    {
        fprintf(stderr, "Not enough arguments: need number and filename.\n");
        return EXIT_FAILURE;
    }
    if (argc == 1)
    {
        fprintf(stderr, "Not enough arguments: need filename.\n");
        return EXIT_FAILURE;
    }

    int number;
    if (sscanf(argv[0], "%d", &number) != 1 || number <= 0)
    {
        fprintf(stderr, "Invalid second argument. "
            "It must be positive number.\n");
        return EXIT_FAILURE;
    }

    generate_file(argv[1], number);
    // printf("Successful.\n");

    return EXIT_SUCCESS;
}
