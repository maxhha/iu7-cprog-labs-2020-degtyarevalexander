#include "../inc/matrix.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

matrix_t *create_matrix(int w, int h)
{
    matrix_t *m = malloc(sizeof(matrix_t));

    if (m == NULL)
    {
        return NULL;
    }

    m->data = malloc(h * w * sizeof(int));

    if (m->data == NULL)
    {
        free(m);
        return NULL;
    }

    m->width = w;
    m->height = h;

    return m;
}

void free_matrix(matrix_t *m)
{
    free(m->data);
    free(m);
}

matrix_t *read_matrix(char *filename)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        LOG_DEBUG("file not found\n");
        return NULL;
    }

    int h, w;

    if (fscanf(f, "%d %d", &h, &w) != 2 || w <= 0 || h <= 0)
    {
        fclose(f);
        return NULL;
    }

    LOG_DEBUG("w = %d, h = %d\n", w, h);

    matrix_t *m = create_matrix(w, h);

    if (m == NULL)
    {
        fclose(f);
        return NULL;
    }

    LOG_DEBUG("read data\n");

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (fscanf(f, "%d", m->data + x + y * w) != 1)
            {
                free_matrix(m);
                fclose(f);
                return NULL;
            }

    fclose(f);

    return m;
}

matrix_t *get_count_neighboors_matrix(const matrix_t *m)
{
    matrix_t *r = create_matrix(m->width, m->height);

    if (r == NULL)
    {
        return NULL;
    }

    for (int y = 0; y < r->height; y++)
        for (int x = 0; x < r->width; x++)
            r->data[x + y * r->width] = count_neighboors(m, x, y);

    return r;
}

int count_neighboors(const matrix_t *m, int x, int y)
{
    if (m->data[x + y * m->width] != 0)
        return -1;

    int c = 0;

    for (int i = MAX(0, x - 1); i < MIN(m->width, x + 2); i++)
        for (int j = MAX(0, y - 1); j < MIN(m->height, y + 2); j++)
            c += m->data[i + j * m->width] != 0;

    return c;
}

matrix_t *cut_empty_columns(const matrix_t *m)
{
    int r_width = 0;

    for (int x = 0; x < m->width; x++)
    {
        int nonzero = 0;
        for (int y = 0; y < m->height; y++)
            nonzero |= m->data[x + y * m->width] != 0;

        r_width += nonzero;
    }

    if (r_width == 0)
    {
        LOG_DEBUG("all columns is empty\n");
        return NULL;
    }

    matrix_t *r = create_matrix(r_width, m->height);

    if (r == NULL)
        return NULL;

    for (int x = 0, r_x = 0; x < m->width; x++)
    {
        int nonzero = 0;
        for (int y = 0; y < m->height; y++)
            nonzero |= m->data[x + y * m->width] != 0;

        if (nonzero == 0)
            continue;

        for (int y = 0; y < m->height; y++)
        {
            r->data[r_x + y * r->width] = m->data[x + y * m->width];
        }

        r_x++;
    }

    return r;
}

int write_matrix(char *filename, const matrix_t *m)
{
    FILE *f = fopen(filename, "w");

    if (f == NULL)
    {
        LOG_DEBUG("cant write to file\n");

        return EXIT_FAILURE;
    }

    fprintf(f, "%d %d\n", m->height, m->width);

    for (int y = 0; y < m->height; y++)
        for (int x = 0; x < m->width; x++)
        {
            int val = m->data[x + y * m->width];
            fprintf(f, "%2d%c", val, x == m->width - 1 ? '\n' : ' ');
        }

    fclose(f);

    return EXIT_SUCCESS;
}
