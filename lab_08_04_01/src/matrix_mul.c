#include "../inc/matrix_mul.h"

matrix_t *multiply_matrix(const matrix_t *a, const matrix_t *b)
{
    LOG_DEBUG("a = %p, b = %p", (void *) a, (void *) b);

    LOG_DEBUG("a->width = %lu, b->width = %lu", a->width, b->width);

    if (a->width != b->height)
    {
        LOG_ERROR("a->width != b->width%s", "");
        return NULL;
    }

    size_t w = b->width;
    size_t h = a->height;
    size_t n = a->width;

    LOG_DEBUG("w = %lu, h = %lu, n = %lu", w, h, n);
    LOG_DEBUG("create result matrix%s", "");

    matrix_t *r = create_matrix(w, h);

    if (r == NULL)
    {
        LOG_ERROR("cant create result matrix%s", "");
        return NULL;
    }

    LOG_DEBUG("perform multiplication%s", "");

    LOG_DEBUG("xa\t ya\t ia\t xb\t yb\t ib\t ia*ib\t sum%s", "");

    for (size_t y = 0; y < h; y++)
        for (size_t x = 0; x < w; x++)
        {
            int sum = 0;
            for (size_t i = 0; i < n; i++)
            {
                sum += a->data[i + y * n] * b->data[x + i * w];
                LOG_DEBUG("%lu\t %lu\t %d\t %lu\t %lu\t %d\t %d\t %d", \
                    i, y, a->data[i + y * n], \
                    x, i, b->data[x + i * w], \
                    a->data[i + y * n] * b->data[x + i * w], sum); \
            }
            LOG_DEBUG("-------------------------------------%s", "");

            r->data[x + y * w] = sum;
        }

    LOG_DEBUG("result:%s", "");
    LOG_DEBUG_MATRIX(r);

    LOG_DEBUG("return %p", (void *) r);

    return r;
}

matrix_t *get_matrix_power(const matrix_t *m, size_t pwr)
{
    LOG_DEBUG("m = %p, pwr = %lu", (void *) m, pwr);

    LOG_DEBUG("create result matrix%s", "");
    matrix_t *r = create_matrix(m->width, m->height);

    if (r == NULL)
    {
        LOG_ERROR("failed to create result matrix%s", "");
        return NULL;
    }

    LOG_DEBUG("create power matrix%s", "");
    matrix_t *pwr_m = create_matrix(m->width, m->height);

    if (pwr_m == NULL)
    {
        free_matrix(r);
        LOG_ERROR("failed to create result matrix%s", "");
        return NULL;
    }

    LOG_DEBUG("fill result matrix and power_matrix as E%s", "");

    for (size_t y = 0; y < m->height; y++)
        for (size_t x = 0; x < m->width; x++)
            pwr_m->data[x + y * m->width] = r->data[x + y * m->width] = x == y;

    LOG_DEBUG("gather powers of matrix%s", "");

    for (; pwr > 0; pwr /= 2)
    {
        LOG_DEBUG("pwr = %lu", pwr);
        matrix_t *tmp_pwr_m = multiply_matrix(pwr_m, m);

        if (tmp_pwr_m == NULL)
        {
            LOG_ERROR("cant get power%s", "");
            free_matrixes(2, pwr_m, r);
            return NULL;
        }

        free_matrix(pwr_m);
        pwr_m = tmp_pwr_m;

        if (pwr % 2 == 0)
            continue;

        LOG_DEBUG("mul matrix%s", "");

        matrix_t *tmp_r = multiply_matrix(r, pwr_m);

        if (tmp_r == NULL)
        {
            LOG_ERROR("cant get new result%s", "");
            free_matrixes(2, pwr_m, r);
            return NULL;
        }

        free_matrix(r);
        r = tmp_r;
    }

    free_matrix(pwr_m);

    LOG_DEBUG("result:%s", "");
    LOG_DEBUG_MATRIX(r);

    return r;
}
