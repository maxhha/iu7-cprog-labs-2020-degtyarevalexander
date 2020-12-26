#include "../inc/main.h"

#define FILE_IN "in.txt"
#define FILE_OUT "out.txt"

int main(void)
{
    matrix_t *m = read_matrix(FILE_IN);

    LOG_MATRIX(m);

    if (m == NULL)
    {
        LOG_DEBUG("read failed\n");
        return EXIT_FAILURE;
    }

    matrix_t *neighboors = get_count_neighboors_matrix(m);

    if (neighboors == NULL)
    {
        LOG_DEBUG("fail get neighboors matrix\n");

        free_matrix(m);
        return EXIT_FAILURE;
    }

    free_matrix(m);

    LOG_DEBUG("neighboors matrix:\n");
    LOG_MATRIX(neighboors);

    matrix_t *cutted = cut_empty_columns(neighboors);

    if (cutted == NULL)
    {
        LOG_DEBUG("fail get cutted matrix\n");

        free_matrix(neighboors);
        return EXIT_FAILURE;
    }

    free_matrix(neighboors);

    LOG_DEBUG("cutted matrix:\n");
    LOG_MATRIX(cutted);

    int rc = write_matrix(FILE_OUT, cutted);

    free_matrix(cutted);
    
    return rc;
}
