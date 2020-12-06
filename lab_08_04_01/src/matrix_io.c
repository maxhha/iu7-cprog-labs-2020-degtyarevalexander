#include "../inc/matrix_io.h"

matrix_t *scan_matrix(void)
{
    int w, h;

    LOG_DEBUG("scan matrix size%s", "");

    if (scanf("%d %d", &h, &w) != 2)
    {
        LOG_ERROR("invalid width or height input%s", "");
        return NULL;
    }

    LOG_DEBUG("readed w = %d; h = %d", w, h);

    if (w <= 0 || h <= 0)
    {
        LOG_ERROR("width or height is not positive%s", "");
        return NULL;
    }

    matrix_t *m = create_matrix(w, h);

    if (m == NULL)
    {
        LOG_ERROR("matrix not created%s", "");
        return NULL;
    }

    LOG_DEBUG("fill matrix%s", "");

    for (int *i = m->data, *end = m->data + w * h; i < end; i++)
    {
        if (scanf("%d", i) != 1)
        {
            LOG_ERROR("invalid element input%s", "");
            free_matrix(m);
            return NULL;
        }
        LOG_DEBUG("data[%lu, %lu] = %d", (i - m->data) % w, (i - m->data) / w, *i);
    }

    LOG_DEBUG("result:%s", "");
    LOG_DEBUG_MATRIX(m);

    LOG_DEBUG("scanned to %p", (void *) m);
    return m;
}

void print_matrix(const matrix_t *m)
{
    LOG_DEBUG("m = %p", (void *) m);

    for (size_t y = 0; y < m->height; y++)
    {
        int *m_row = m->data + y * m->width;

        printf("%d", *m_row);

        for (size_t x = 1; x < m->width; x++)
            printf(" %d", *(m_row + x));

        printf("\n");
    }
}
