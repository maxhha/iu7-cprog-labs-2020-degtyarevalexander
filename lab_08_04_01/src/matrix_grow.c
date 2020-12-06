#include "../inc/matrix_grow.h"

matrix_t *grow_matrix_rows(const matrix_t *m, size_t height)
{
    LOG_DEBUG("m = %p, height = %lu", (void *) m, height);
    LOG_DEBUG("m->height = %lu", m->height);

    if (m->height >= height)
    {
        LOG_ERROR("matrix height is not less than target height%s", "");
        return NULL;
    }

    matrix_t *r = create_matrix(m->width, height);

    if (r == NULL)
    {
        LOG_ERROR("cant create result matrix%s", "");
        return NULL;
    }

    LOG_DEBUG("copy data to result matrix%s", "");
    memcpy(r->data, m->data, m->height * m->width * sizeof(int));

    LOG_DEBUG("fill new rows%s", "");

    LOG_DEBUG("x\tmean%s", "");

    for (size_t x = 0; x < m->width; x++)
    {
        int sum = 0;

        for (size_t y = 0; y < m->height; y++)
            sum += m->data[x + y * m->width];

        int mean = sum / m->height;

        LOG_DEBUG("%lu\t%d", x, mean);

        for (size_t y = m->height; y < height; y++)
            r->data[x + y * r->width] = mean;
    }

    LOG_DEBUG("result:%s", "");
    LOG_DEBUG_MATRIX(r);

    LOG_DEBUG("return %p", (void *) r);

    return r;
}

matrix_t *grow_matrix_columns(const matrix_t *m, size_t width)
{
    LOG_DEBUG("m = %p, width = %lu", (void *) m, width);
    LOG_DEBUG("m->width = %lu", m->width);

    if (m->width >= width)
    {
        LOG_ERROR("matrix width is not less than target width%s", "");
        return NULL;
    }

    matrix_t *r = create_matrix(width, m->height);

    if (r == NULL)
    {
        LOG_ERROR("cant create result matrix%s", "");
        return NULL;
    }

    LOG_DEBUG("copy data to result matrix%s", "");
    for (size_t y = 0; y < m->height; y++)
        memcpy(r->data + y * r->width, m->data + y * m->width, m->width * sizeof(int));

    LOG_DEBUG("fill new columns%s", "");
    LOG_DEBUG("y\tmin%s", "");

    for (size_t y = 0; y < m->height; y++)
    {
        int *m_row = m->data + y * m->width;
        int min_el = *m_row;

        for (size_t x = 1; x < m->width; x++)
            if (min_el > *(x + m_row))
                min_el = *(x + m_row);

        LOG_DEBUG("%lu\t%d", y, min_el);

        int *r_row = r->data + y * r->width;

        for (size_t x = m->width; x < r->width; x++)
            *(r_row + x) = min_el;
    }

    LOG_DEBUG("result:%s", "");
    LOG_DEBUG_MATRIX(r);

    LOG_DEBUG("return %p", (void *) r);

    return r;
}

matrix_t *grow_matrix(const matrix_t *m, size_t size)
{
    LOG_DEBUG("m = %p, size = %lu", (void *) m, size);

    LOG_DEBUG("grow rows%s", "");
    matrix_t *r_rows = grow_matrix_rows(m, size);

    if (r_rows == NULL)
    {
        LOG_ERROR("matrix rows growing is broken%s", "");
        return NULL;
    }

    LOG_DEBUG("grow columns%s", "");
    matrix_t *r = grow_matrix_columns(r_rows, size);

    if (r == NULL)
    {
        LOG_ERROR("matrix columns growing is broken%s", "");
        free_matrix(r_rows);
        return NULL;
    }

    free_matrix(r_rows);

    LOG_DEBUG("return %p", (void *) r);

    return r;
}
