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

int cut_matrix_columns(matrix_t *m)
{
    LOG_DEBUG("m = %p", (void *) m);

    LOG_DEBUG("create rest_columns%s", "");

    size_t *rest_columns = malloc(sizeof(size_t) * m->width);

    if (rest_columns == NULL)
    {
        LOG_ERROR("rest_columns not created%s", "");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < m->width; i++)
        rest_columns[i] = i;

    LOG_DEBUG("filter columns%s", "");

    for (size_t w = m->width; w > m->height; w--)
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
        for (size_t x = 0; x < m->height; x++)
        {
            size_t r_x = rest_columns[x];
            m->data[x + y * m->height] = m->data[r_x + y * m->width];
        }
    }

    free(rest_columns);

    int *tmp = realloc(m->data, m->height * m->height * sizeof(int));

    if (tmp == NULL)
    {
        LOG_ERROR("fail to realloc%s", "")
        return EXIT_FAILURE;
    }

    m->data = tmp;
    m->width = m->height;

    LOG_DEBUG("result:%s", "");
    LOG_DEBUG_MATRIX(m);

    return EXIT_SUCCESS;
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

int cut_matrix_rows(matrix_t *m)
{
    LOG_DEBUG("m = %p", (void *) m);

    size_t *rest_rows = malloc(sizeof(size_t) * m->height);

    if (rest_rows == NULL)
    {
        LOG_ERROR("rest_rows not created%s", "");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < m->height; i++)
        rest_rows[i] = i;

    LOG_DEBUG("filter rows%s", "");

    for (size_t h = m->height; h > m->width; h--)
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

    for (size_t y = 0; y < m->width; y++)
    {
        size_t m_y = rest_rows[y] * m->width;

        memmove(m->data + y * m->width, m->data + m_y, m->width * sizeof(int));
    }

    free(rest_rows);

    int *tmp = realloc(m->data, m->width * m->width * sizeof(int));

    if (tmp == NULL)
    {
        LOG_ERROR("fail to realloc%s", "")
        return EXIT_FAILURE;
    }

    m->data = tmp;
    m->height = m->width;

    LOG_DEBUG("result:%s", "");
    LOG_DEBUG_MATRIX(m);

    return EXIT_SUCCESS;
}

int cut_matrix(matrix_t *m)
{
    LOG_DEBUG("m->width = %lu, m->height = %lu", m->width, m->height);

    if (m->width < m->height)
        return cut_matrix_rows(m);
    else if (m->width > m->height)
        return cut_matrix_columns(m);

    return EXIT_SUCCESS;
}

int cut_matrixes(int n, ...)
{
    va_list args;

    va_start(args, n);

    int i = 0;

    while (i < n)
    {
        matrix_t *m = va_arg(args, matrix_t *);

        if (cut_matrix(m))
            break;

        i++;
    }

    va_end(args);

    return i;
}
