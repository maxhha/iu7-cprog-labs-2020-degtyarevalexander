#include "../inc/matrix_memory.h"

matrix_t *create_matrix(size_t width, size_t height)
{
    LOG_DEBUG("width = %lu, height = %lu", width, height);
    matrix_t *m = malloc(sizeof(matrix_t));

    if (m == NULL)
    {
        LOG_ERROR("cant malloc for matrix_t%s", "");
        return NULL;
    }

    LOG_DEBUG("create data%s", "");
    m->data = malloc(width * height * sizeof(int));

    if (m->data == NULL)
    {
        LOG_ERROR("cant malloc for data %lux%lu", width, height);
        return NULL;
    }

    m->width = width;
    m->height = height;

    LOG_DEBUG("created %p", (void *) m);

    return m;
}

void free_matrix(matrix_t *m)
{
    LOG_DEBUG("m = %p", (void *) m);

    free(m->data);
    free(m);
}
