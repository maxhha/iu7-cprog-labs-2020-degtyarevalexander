#include "../inc/main.h"

int compare_numbers(const void *a, const void *b)
{
    int *a_num = (int *) a;
    int *b_num = (int *) b;
    return *b_num - *a_num;
}

int main(int argc, char const **argv) {

    if (argc < 3 || argc > 4)
        return EXIT_FAILURE;

    FILE *fin = fopen(*(argv + 1), "r");

    if (fin == NULL)
        return EXIT_FAILURE;

    int *array;
    size_t array_n;

    if (read_array(fin, &array, &array_n) != OK)
    {
        fclose(fin);
        return EXIT_FAILURE;
    }

    fclose(fin);

    if (argc == 4)
    {
        if (strcmp(*(argv + 3), FILTER_ARG) != 0)
        {
            free(array);
            return EXIT_FAILURE;
        }

        int *filtered_begin, *filtered_end;

        if (key(array, array + array_n, &filtered_begin, &filtered_end) != OK)
        {
            free(array);
            return EXIT_FAILURE;
        }

        free(array);
        array = filtered_begin;
        array_n = filtered_end - filtered_begin;
    }

    mysort(array, array_n, sizeof(*array), compare_numbers);

    FILE *fout = fopen(*(argv + 2), "w");

    if (fout == NULL)
        return EXIT_FAILURE;

    write_array(fout, array, array_n);

    fclose(fout);
    free(array);

    return EXIT_SUCCESS;
}
