#include "../inc/main.h"

int compare_numbers(const void *a, const void *b)
{
    int *a_num = (int *) a;
    int *b_num = (int *) b;
    return *a_num - *b_num;
}

int main(int argc, char const **argv) {

    if (argc < 3 || argc > 4)
        return EXIT_FAILURE;

    FILE *fin = fopen(*(argv + 1), "r");

    if (fin == NULL)
        return EXIT_FAILURE;

    int *b_array, *e_array;

    if (read_array(fin, &b_array, &e_array) != OK)
    {
        fclose(fin);
        return EXIT_FAILURE;
    }

    fclose(fin);

    if (argc == 4)
    {
        if (strcmp(*(argv + 3), FILTER_ARG) != 0)
        {
            free(b_array);
            return EXIT_FAILURE;
        }

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

    FILE *fout = fopen(*(argv + 2), "w");

    if (fout == NULL)
        return EXIT_FAILURE;

    write_array(fout, b_array, e_array);

    fclose(fout);
    free(b_array);

    return EXIT_SUCCESS;
}
