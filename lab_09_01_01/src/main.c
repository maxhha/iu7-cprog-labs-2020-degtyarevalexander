#include "../inc/main.h"

union arguments_key
{
    int int_data;
    char *char_ptr_data;
};

struct arguments
{
    char *file;
    int field;
    bool have_key;
    union arguments_key key;
};

struct arguments *parse_args(int argc, char *argv[])
{
    LOG_DEBUG("argc = %d", argc);

    if (argc < 3 || argc > 4)
    {
        LOG_ERROR("at least 2 and max 3 arguments must be passed%s", "");
        return NULL;
    }

    LOG_DEBUG("argv[1] = \"%s\"", argv[1]);
    LOG_DEBUG("argv[2] = \"%s\"", argv[2]);

    int field;

    if (strcmp(argv[2], ARG_FIELD_TITLE) == 0)
    {
        field = FILM_FIELD_TITLE;
    }
    else if (strcmp(argv[2], ARG_FIELD_NAME) == 0)
    {
        field = FILM_FIELD_NAME;
    }
    else if (strcmp(argv[2], ARG_FIELD_YEAR) == 0)
    {
        field = FILM_FIELD_YEAR;
    }
    else
    {
        LOG_ERROR("unknown argv[1] field type%s", "");
        return NULL;
    }

    struct arguments *a = malloc(sizeof(struct arguments));

    if (a == NULL)
    {
        LOG_ERROR("no mem for struct arguments%s", "");
        return NULL;
    }

    a->file = argv[1];
    a->field = field;
    a->have_key = false;
    a->key.char_ptr_data = NULL;

    if (argc < 4)
        return a;

    a->have_key = true;


    LOG_DEBUG("argv[3] = \"%s\"", argv[3]);

    if (field == FILM_FIELD_YEAR)
    {
        if (sscanf(argv[3], "%d", &a->key.int_data) != 1)
        {
            LOG_ERROR("cant parse year from argv[3]%s", "");
            free(a);
            return NULL;
        }
    }
    else
    {
        a->key.char_ptr_data = argv[3];
    }

    return a;
}

int main(int argc, char **argv)
{
    struct arguments *args = parse_args(argc, argv);

    if (args == NULL)
    {
        LOG_ERROR("parse args failed%s", "");
        return EXIT_FAILURE;
    }

    film_t **films_arr;
    int films_n = read_films_from_file(args->file, args->field, &films_arr);

    if (films_n < 1)
    {
        LOG_ERROR("error on reading or no films in file%s", "");
        free(args);
        return EXIT_FAILURE;
    }

    if (!args->have_key)
    {
        print_films_array(films_arr, films_n);
        free_films_array(films_arr, films_n);
        free(args);

        return EXIT_SUCCESS;
    }

    film_t search_key = {0};

    if (args->field == FILM_FIELD_TITLE)
    {
        LOG_DEBUG("search by title \"%s\"", args->key.char_ptr_data);
        search_key.title = args->key.char_ptr_data;
    }
    else if (args->field == FILM_FIELD_NAME)
    {
        LOG_DEBUG("search by name \"%s\"", args->key.char_ptr_data);
        search_key.name = args->key.char_ptr_data;
    }
    else
    {
        LOG_DEBUG("search by year %d", args->key.int_data);
        search_key.year = args->key.int_data;
    }

    film_t *key_p = &search_key;

    int (*cmp)(const void *, const void *) = CMP_FILMS_BY(args->field);

    film_t **p = bsearch(&key_p, films_arr, films_n, sizeof(film_t *), cmp);

    if (p == NULL)
    {
        LOG_DEBUG("not found%s", "");
        printf("Not found\n");
    }
    else
    {
        LOG_DEBUG("found at %d pos", (int) (p - films_arr));
        print_films_array(p, 1);
    }

    free_films_array(films_arr, films_n);
    free(args);

    return EXIT_SUCCESS;
}
