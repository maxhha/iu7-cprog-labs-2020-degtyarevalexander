#include "../inc/main.h"

int compare_numbers(const void *a, const void *b)
{
    int a_num = *(int *) a;
    int b_num = *(int *) b;
    return a_num < b_num ? -1 : a_num == b_num ? 0 : 1;
}

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

    FILE *fin = fopen(filename_in, "r");

    if (fin == NULL)
        return EXIT_FAILURE;

    int *b_array, *e_array;

    if (read_array(fin, &b_array, &e_array) != OK)
    {
        fclose(fin);
        return EXIT_FAILURE;
    }

    if (fclose(fin))
        exit(EXIT_FAILURE);

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

    FILE *fout = fopen(filename_out, "w");

    if (fout == NULL)
    {
        free(b_array);
        return EXIT_FAILURE;
    }

    write_array(fout, b_array, e_array);

    fclose(fout);
    free(b_array);

    return EXIT_SUCCESS;
}
