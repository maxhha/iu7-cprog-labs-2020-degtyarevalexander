#include "../inc/main.h"

int main(int argc, char **argv)
{
    if (argc != 4)
        return EXIT_FAILURE;

    char *filein = argv[1], *fileout = argv[2], op = argv[3][0];

    LOG_DEBUG("filein = \"%s\"", filein);
    LOG_DEBUG("fileout = \"%s\"", fileout);
    LOG_DEBUG("op = '%c'", op);

    node_t *in_list = read_csv(filein), *out_list = NULL;

    if (!in_list)
    {
        LOG_ERROR("fail to read file%s", "");
        return EXIT_FAILURE;
    }

    if (op == OP_FIND)
    {
        out_list = operation_find(&in_list);
    }
    else if (op == OP_FIRST)
    {
        out_list = operation_first(&in_list);
    }
    else if (op == OP_REVERSE)
    {
        out_list = operation_reverse(&in_list);
    }
    else if (op == OP_SORT_DATE)
    {
        out_list = operation_sort_by_date(&in_list);
    }

    int rc;

    if (out_list)
    {
        write_csv(fileout, out_list);
        free_list(out_list, (void (*)(void *)) free_transaction);
        rc = EXIT_SUCCESS;
    }
    else
    {
        LOG_ERROR("no out list%s", "");
        rc = EXIT_FAILURE;
    }

    if (in_list)
        free_list(in_list, (void (*)(void *)) free_transaction);

    return rc;
}
