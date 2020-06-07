#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define CREATE_BIN "cb"
#define SORT_TXT "st"
#define SORT_BIN "sb"
#define FIND_TXT "ft"
#define FIND_BIN "fb"
#define DELETE_TXT "dt"
#define DELETE_BIN "db"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments\n");
        return EXIT_FAILURE;
    }

    char *cmd = argv[1];
    argv[1] = argv[0];

    if (strcmp(cmd, CREATE_BIN) == 0)
    {
        return main_create(argc - 1, argv + 1);
    }

    if (strcmp(cmd, SORT_TXT) == 0)
    {
        return EWRONG_FILE;
    }

    if (strcmp(cmd, SORT_BIN) == 0)
    {
        return main_sort_bin(argc - 1, argv + 1);
    }

    if (strcmp(cmd, FIND_TXT) == 0)
    {
        return EWRONG_FILE;
    }

    if (strcmp(cmd, FIND_BIN) == 0)
    {
        return main_find_bin(argc - 1, argv + 1);
    }

    if (strcmp(cmd, DELETE_TXT) == 0)
    {
        return EWRONG_FILE;
    }

    if (strcmp(cmd, DELETE_BIN) == 0)
    {
        return main_delete_bin(argc - 1, argv + 1);
    }

    return EXIT_FAILURE;
}
