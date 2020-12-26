#include "../inc/main.h"

int parse_args(int argc, char **argv, char **filein, char **fileout)
{
    if (argc < 3 || argc > 3)
    {
        return EXIT_FAILURE;
    }

    *filein = argv[1];
    *fileout = argv[2];

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    char *filein;
    char *fileout;

    if (parse_args(argc, argv, &filein, &fileout) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    char_list_t *list = read_list_from_file(filein);

    list = reverse(list);

    int rc = write_list_to_file(fileout, list);

    free_char_list(list);

    return rc;
}
