#ifndef __FILM_TABLE_H__
#define __FILM_TABLE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

typedef struct {
    char *title;
    char *name;
    int year;
} film_t;

#define OK 0
#define EREAD -1
#define ENODATA -2

#define FILM_FIELD_TITLE 0
#define FILM_FIELD_NAME 1
#define FILM_FIELD_YEAR 2

#define CMP_FILMS_BY(field) ( \
    (field) == FILM_FIELD_NAME ? cmp_films_by_name : \
    (field) == FILM_FIELD_YEAR ? cmp_films_by_year : \
    cmp_films_by_title)

int cmp_films_by_title(const void *a, const void *b);
int cmp_films_by_name(const void *a, const void *b);
int cmp_films_by_year(const void *a, const void *b);

void free_film(film_t *film);
void free_films_array(film_t **film, size_t n);

int read_films_from_file(const char *filename, int sort_field, film_t ***result);
void print_films_array(film_t **films_arr, int n);

#endif // __FILM_TABLE_H__
