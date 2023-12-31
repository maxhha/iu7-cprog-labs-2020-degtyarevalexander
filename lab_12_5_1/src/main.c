#include "../inc/main.h"

int parse_args(int argc, char **argv, char **filein, char **fileout, bool *filter)
{
    if (argc < 3 || argc > 4)
        return PARSE_ARGS_ERR;

    *filein = argv[1];
    *fileout = argv[2];

    if (argc == 4)
    {
        if (strcmp(*(argv + 3), FILTER_ARG) != 0)
            return PARSE_ARGS_ERR;

        *filter = true;
    }

    return PARSE_ARGS_OK;
}

int main(int argc, char **argv)
{
    #ifdef __USE_DYNLIN__

    void *hlib = dlopen(LIB_PATH, RTLD_NOW);

    if (hlib == NULL)
        return EXIT_FAILURE;

    #define LOAD(name) \
        dl ## name ## _t name; \
        *((void **) (&(name))) = dlsym(hlib, # name ); \
        if (name == NULL) \.
        { \
            dlclose(hlib); \
            return EXIT_FAILURE; \
        }

    LOAD(key)
    LOAD(mysort)
    LOAD(write_array_to_file)
    LOAD(read_array_from_file)
    LOAD(compare_numbers)

    #else

    #endif // __USE_DYNLIN__

    char *filename_in = NULL;
    char *filename_out = NULL;
    bool filter = false;

    if (parse_args(argc, argv, &filename_in, &filename_out, &filter) == PARSE_ARGS_ERR)
    {
        #ifdef __USE_DYNLIN__
        dlclose(hlib);
        #endif // __USE_DYNLIN__

        return EXIT_FAILURE;
    }

    int *b_array, *e_array;

    if (read_array_from_file(filename_in, &b_array, &e_array) != OK)
    {
        #ifdef __USE_DYNLIN__
        dlclose(hlib);
        #endif // __USE_DYNLIN__

        return EXIT_FAILURE;
    }

    if (filter)
    {
        int n = key(b_array, e_array, NULL, NULL);

        if (n <= 0)
        {
            free(b_array);

            #ifdef __USE_DYNLIN__
            dlclose(hlib);
            #endif // __USE_DYNLIN__

            return EXIT_FAILURE;
        }

        int *b_filtered = malloc(n * sizeof(int)), *e_filtered;

        if (b_filtered == NULL)
        {
            free(b_array);

            #ifdef __USE_DYNLIN__
            dlclose(hlib);
            #endif // __USE_DYNLIN__

            return EXIT_FAILURE;
        }

        if (key(b_array, e_array, &b_filtered, &e_filtered) != n)
        {
            free(b_array);
            free(b_filtered);

            #ifdef __USE_DYNLIN__
            dlclose(hlib);
            #endif // __USE_DYNLIN__

            return EXIT_FAILURE;
        }

        free(b_array);
        b_array = b_filtered;
        e_array = e_filtered;
    }

    mysort(b_array, e_array - b_array, sizeof(*b_array), compare_numbers);

    int rc = write_array_to_file(filename_out, b_array, e_array);

    free(b_array);

    #ifdef __USE_DYNLIN__
    dlclose(hlib);
    #endif // __USE_DYNLIN__

    return rc == OK ? EXIT_SUCCESS : EXIT_FAILURE;
}
