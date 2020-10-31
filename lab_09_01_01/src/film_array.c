#include "../inc/film_array.h"

int cmp_films_by_title(const void *a, const void *b)
{
    const film_t *fa = (*((const film_t **) a));
    const film_t *fb = (*((const film_t **) b));
    return strcmp(fa->title, fb->title);
}

int cmp_films_by_name(const void *a, const void *b)
{
    const film_t *fa = (*((const film_t **) a));
    const film_t *fb = (*((const film_t **) b));
    return strcmp(fa->name, fb->name);
}

int cmp_films_by_year(const void *a, const void *b)
{
    int year_a = (*((const film_t **) a))->year;
    int year_b = (*((const film_t **) b))->year;
    return year_a < year_b ? -1 : year_a == year_b ? 0 : 1;
}

int scan_film(FILE *f, film_t **film)
{
    char *buf = NULL;
    size_t buf_size = 0;

    int str_len = getline(&buf, &buf_size, f);

    if (str_len == -1)
    {
        LOG_DEBUG("no new line%s", "");

        if (buf != NULL)
            free(buf);

        return ENODATA;
    }

    if (str_len < 2)
    {
        LOG_ERROR("title is empty%s", "");

        free(buf);
        return EREAD;
    }

    buf[str_len - 1] = '\0';

    LOG_DEBUG("title = \"%s\"", buf);

    char *title = strdup(buf);

    if (title == NULL)
    {
        LOG_ERROR("no mem for title%s", "");
        free(buf);
        return EREAD;
    }

    str_len = getline(&buf, &buf_size, f);

    if (str_len < 2)
    {
        LOG_ERROR("no name in file%s", "");
        free(title);
        free(buf);
        return EREAD;
    }

    buf[str_len - 1] = '\0';

    LOG_DEBUG("name = \"%s\"", buf);

    char *name = strdup(buf);

    if (name == NULL)
    {
        LOG_ERROR("no mem for name%s", "");
        free(title);
        free(buf);
        return EREAD;
    }

    str_len = getline(&buf, &buf_size, f);

    if (str_len < 2)
    {
        LOG_ERROR("no year in file%s", "");
        free(name);
        free(title);
        free(buf);
        return EREAD;
    }

    int year;

    if (sscanf(buf, "%d", &year) != 1 || year <= 0)
    {
        LOG_ERROR("cant read year%s","");
        free(name);
        free(title);
        free(buf);
        return EREAD;
    }

    LOG_DEBUG("year = %d", year);

    *film = malloc(sizeof(film_t));

    (*film)->title = title;
    (*film)->name = name;
    (*film)->year = year;

    free(buf);
    return OK;
}

void free_film(film_t *film)
{
    free(film->name);
    free(film->title);
    free(film);
}

void free_films_array(film_t **films, size_t n)
{
    film_t **end = films + n;

    LOG_DEBUG("free %lu films", n);

    for (film_t **i = films; i < end; i++)
        free_film(*i);

    free(films);
}

int read_films_from_file(const char *filename, int sort_field, film_t ***result)
{
    LOG_DEBUG("filename = %s; sort_field = %d", filename, sort_field);

    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        LOG_ERROR("cant open file%s", "");
        return EREAD;
    }

    int (*cmp)(const void *a, const void *b) = CMP_FILMS_BY(sort_field);

    int n = 0;
    int capacity = 4;
    film_t **film_arr = malloc(capacity * sizeof(film_t *));
    film_t *curr;

    while (feof(f) == 0)
    {
        LOG_DEBUG("read %d film", n);

        int rc = scan_film(f, &curr);

        if (rc == ENODATA)
            break;

        if (rc != OK)
        {
            LOG_ERROR("read film error%s", "");
            free_films_array(film_arr, n);
            fclose(f);
            return EREAD;
        }

        if (n == capacity)
        {
            capacity *= 2;

            LOG_DEBUG("malloc for %d", capacity);

            film_t **tmp = realloc(film_arr, capacity * sizeof(film_t *));

            if (tmp == NULL)
            {
                LOG_ERROR("cant malloc for %d elements", capacity);
                free_film(curr);
                free_films_array(film_arr, n);
                fclose(f);
                return EREAD;
            }

            film_arr = tmp;
        }

        film_t **end = film_arr + n;

        film_t **p = film_arr;

        while (p < end && cmp(p, &curr) <= 0)
            p++;

        LOG_DEBUG("insert at %d", (int) (p - film_arr));

        for (film_t **i = end; i > p; i--)
            *i = *(i - 1);

        *p = curr;
        n++;
    }

    if (n == 0)
    {
        LOG_ERROR("file is empty%s", "");
        free(film_arr);
        fclose(f);
        return ENODATA;
    }

    film_t **tmp = realloc(film_arr, n * sizeof(film_t *));

    if (tmp != NULL)
        film_arr = tmp;

    #if LOG_LEVEL >= DEBUG_LEVEL

    LOG_DEBUG("readed %d films", n);
    LOG_DEBUG("%-10s | %-10s | %s", "title", "name", "year");

    for (int i = 0; i < n; i++)
    {
        film_t *film = film_arr[i];
        LOG_DEBUG("%-10s | %-10s | %d", film->title, film->name, film->year);
    }

    #endif // LOG_LEVEL >= DEBUG_LEVEL

    fclose(f);

    *result = film_arr;

    return n;
}

void print_films_array(film_t **films_arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        film_t *film = films_arr[i];
        printf("%s\n%s\n%d\n", film->title, film->name, film->year);
    }
}
