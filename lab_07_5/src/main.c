#include "../inc/main.h"

int parse_args(int argc, char const **argv, char *filename_in, char *filename_out, bool *filter)
{
    if (argc < 3 || argc > 4)
        return PARSE_ARGS_ERR;

    strncpy(filename_in, *(argv + 1), MAX_FILE_NAME);
    strncpy(filename_out, *(argv + 2), MAX_FILE_NAME);

    if (argc == 4)
    {
        if (strcmp(*(argv + 3), FILTER_ARG) != 0)
            return PARSE_ARGS_ERR;

        *filter = true;
    }

    return PARSE_ARGS_OK;
}

int main(int argc, char const **argv)
{
    char filename_in[MAX_FILE_NAME + 1] = { 0 };
    char filename_out[MAX_FILE_NAME + 1] = { 0 };
    bool filter = false;

    if (parse_args(argc, argv, filename_in, filename_out, &filter) == PARSE_ARGS_ERR)
        return EXIT_FAILURE;

    int *b_array, *e_array;

    if (read_array_from_file(filename_in, &b_array, &e_array) != OK)
    {
        return EXIT_FAILURE;
    }

    if (filter)
    {
        int *b_filtered, *e_filtered;

        if (key(b_array, e_array, &b_filtered, &e_filtered) != OK)
        {
            free(b_array);
            return EXIT_FAILURE;
        }

        free(b_array);
        b_array = b_filtered;
        e_array = e_filtered;
    }

    mysort(b_array, e_array - b_array, sizeof(*b_array), compare_numbers);

    int rc = write_array_to_file(filename_out, b_array, e_array);

    free(b_array);

    return rc == OK ? EXIT_SUCCESS : EXIT_FAILURE;
}
