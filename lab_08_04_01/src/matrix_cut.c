#include "../inc/matrix_cut.h"

int *get_last_max_element_in_column(const matrix_t *m, size_t col)
{
    LOG_DEBUG("m = %p, col = %lu", (void *) m, col);
    int *p = m->data + col;

    LOG_DEBUG("max_y\tmax_el\tx\ty\tdata%s", "");

    for (size_t y = 1; y < m->height; y++)
    {
        LOG_DEBUG("%lu\t%d\t%lu\t%lu\t%d", (p - m->data) / m->width, *p, col, y, m->data[col + y * m->width]);

        if (*p <= m->data[col + y * m->width])
            p = m->data + col + y * m->width;
    }

    LOG_DEBUG("max is M[%lu, %lu] = %d", col, (p - m->data) / m->width, *p);


    return p;
}

matrix_t *cut_matrix_columns(const matrix_t *m)
{
    LOG_DEBUG("m = %p", (void *) m);

    matrix_t *r = create_matrix(m->height, m->height);

    if (r == NULL)
    {
        LOG_ERROR("result matrix not created%s", "");
        return NULL;
    }

    LOG_DEBUG("create rest_columns%s", "");

    size_t *rest_columns = malloc(sizeof(size_t) * m->width);

    if (rest_columns == NULL)
    {
        LOG_ERROR("rest_columns not created%s", "");
        free_matrix(r);
        return NULL;
    }

    for (size_t i = 0; i < m->width; i++)
        rest_columns[i] = i;

    LOG_DEBUG("filter columns%s", "");

    for (size_t w = m->width; w > r->width; w--)
    {
        size_t *max_c = rest_columns;
        size_t *end = rest_columns + w;
        int max_el = m->data[*max_c];

        LOG_DEBUG("max_el = %d, max_c = %lu", max_el, *max_c);

        for (size_t *c = rest_columns; c < end; c++)
        {
            LOG_DEBUG("find max in %lu column", *c);

            int *p = get_last_max_element_in_column(m, *c);

            if (*p < max_el)
                continue;

            max_el = *p;
            max_c = c;

            LOG_DEBUG("max_el = %d, max_c = %lu", max_el, *max_c);
        }

        LOG_DEBUG("remove %lu col", *max_c);

        for (size_t *c = max_c + 1; c < end; c++)
            *(c - 1) = *c;
    }

    #if LOG_LEVEL >= DEBUG_LEVEL
    LOG_DEBUG("rest columns:%s", "");

    for (size_t c = 0; c < m->height; c++)
        LOG_DEBUG("rest_columns[%lu] = %lu", c, rest_columns[c]);

    #endif // LOG_DEBUG

    LOG_DEBUG("copy data to result matrix%s", "");

    for (size_t y = 0; y < m->height; y++)
    {
        int *r_row = r->data + y * r->width;
        int *m_row = m->data + y * m->width;

        for (size_t x = 0; x < m->height; x++)
        {
            size_t m_x = rest_columns[x];
            *(r_row + x) = *(m_row + m_x);

            LOG_DEBUG("data[%lu, %lu] = %d", x, y, *(r_row + x));
        }
    }

    free(rest_columns);

    LOG_DEBUG("result:%s", "");
    LOG_DEBUG_MATRIX(r);

    LOG_DEBUG("return %p", (void *) r);

    return r;
}

int *get_last_max_element_in_row(const matrix_t *m, size_t row)
{
    LOG_DEBUG("m = %p, row = %lu", (void *) m, row);
    int *p = m->data + row * m->width;

    LOG_DEBUG("max_x\tmax_el\tx\ty\tdata%s", "");

    for (size_t x = 1; x < m->width; x++)
    {
        LOG_DEBUG("%lu\t%d\t%lu\t%lu\t%d", (p - m->data) % m->width, *p, x, row, m->data[x + row * m->width]);

        if (*p < m->data[x + row * m->width])
            p = m->data + x + row * m -> width;
    }

    LOG_DEBUG("max is M[%lu, %lu] = %d",  (p - m->data) % m->width, row, *p);
    return p;
}

matrix_t *cut_matrix_rows(const matrix_t *m)
{
    LOG_DEBUG("m = %p", (void *) m);

    matrix_t *r = create_matrix(m->width, m->width);

    if (r == NULL)
    {
        LOG_ERROR("result matrix not created%s", "");
        return NULL;
    }

    size_t *rest_rows = malloc(sizeof(size_t) * m->height);

    if (rest_rows == NULL)
    {
        LOG_ERROR("rest_rows not created%s", "");
        free_matrix(r);
        return NULL;
    }

    for (size_t i = 0; i < m->height; i++)
        rest_rows[i] = i;

    LOG_DEBUG("filter rows%s", "");

    for (size_t h = m->height; h > r->height; h--)
    {
        size_t *max_r = rest_rows;
        size_t max_x = 0;
        size_t *end = rest_rows + h;
        int max_el = m->data[*max_r * m->width];

        LOG_DEBUG("max_el = %d, max_r = %lu, max_x = %lu", max_el, *max_r, max_x);

        for (size_t *r = rest_rows; r < end; r++)
        {
            LOG_DEBUG("find max in %lu row", *r);

            int *p = get_last_max_element_in_row(m, *r);

            size_t x = (p - m->data) % m->width;

            if (*p < max_el || (*p == max_el && max_x > x))
                continue;

            max_el = *p;
            max_r = r;
            max_x = x;

            LOG_DEBUG("max_el = %d, max_r = %lu, max_x = %lu", max_el, *max_r, max_x);
        }

        LOG_DEBUG("remove %lu row", *max_r);

        for (size_t *r = max_r + 1; r < end; r++)
            *(r - 1) = *r;
    }

    #if LOG_LEVEL >= DEBUG_LEVEL
    LOG_DEBUG("rest rows:%s", "");

    for (size_t r = 0; r < m->width; r++)
        LOG_DEBUG("rest_rows[%lu] = %lu", r, rest_rows[r]);

    #endif // LOG_DEBUG

    LOG_DEBUG("copy data to result matrix%s", "");

    for (size_t y = 0; y < r->height; y++)
    {
        size_t m_y = rest_rows[y] * m->width;
        int *m_row = m->data + m_y;
        int *r_row = r->data + y * r->width;

        for (size_t x = 0; x < r->width; x++)
        {
            *(r_row + x) = *(m_row + x);

            LOG_DEBUG("data[%lu, %lu] = %d", x, y, *(r_row + x));
        }
    }

    free(rest_rows);

    LOG_DEBUG("result:%s", "");
    LOG_DEBUG_MATRIX(r);

    LOG_DEBUG("return %p", (void *) r);

    return r;
}

matrix_t *cut_matrix(const matrix_t *m)
{
    LOG_DEBUG("m->width = %lu, m->height = %lu", m->width, m->height);

    if (m->width < m->height)
        return cut_matrix_rows(m);
    else if (m->width > m->height)
        return cut_matrix_columns(m);

    LOG_DEBUG("make copy%s", "");

    matrix_t *r = create_matrix(m->width, m->height);

    if (r == NULL)
    {
        LOG_ERROR("cant create result matrix%s", "");
        return NULL;
    }

    memcpy(r->data, m->data, m->width * m->height * sizeof(int));

    return r;
}
