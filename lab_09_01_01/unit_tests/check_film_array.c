#include "../inc/check_film_array.h"

START_TEST(scan_film_from_empty_stream)
{
    char data[] = "";
    film_t *film = NULL;

    FILE *stream = fmemopen(data, strlen(data), "r");
    ck_assert_ptr_nonnull(stream);

    int rc = scan_film(stream, &film);
    fclose(stream);

    ck_assert_int_ne(rc, OK);
    ck_assert_ptr_null(film);
}
END_TEST

START_TEST(scan_film_with_empty_title)
{
    char data[] = "\n";
    film_t *film = NULL;

    FILE *stream = fmemopen(data, strlen(data), "r");
    ck_assert_ptr_nonnull(stream);

    int rc = scan_film(stream, &film);
    fclose(stream);

    ck_assert_int_ne(rc, OK);
    ck_assert_ptr_null(film);
}
END_TEST

START_TEST(scan_film_with_empty_name)
{
    char data[] = "title\n\n";
    film_t *film = NULL;

    FILE *stream = fmemopen(data, strlen(data), "r");
    ck_assert_ptr_nonnull(stream);

    int rc = scan_film(stream, &film);
    fclose(stream);

    ck_assert_int_ne(rc, OK);
    ck_assert_ptr_null(film);
}
END_TEST

START_TEST(scan_film_with_empty_year)
{
    char data[] = "title\nname\n\n";
    film_t *film = NULL;

    FILE *stream = fmemopen(data, strlen(data), "r");
    ck_assert_ptr_nonnull(stream);

    int rc = scan_film(stream, &film);
    fclose(stream);

    ck_assert_int_ne(rc, OK);
    ck_assert_ptr_null(film);
}
END_TEST

START_TEST(scan_film_with_empty_neg_year)
{
    char data[] = "title\nname\n-2020\n";
    film_t *film = NULL;

    FILE *stream = fmemopen(data, strlen(data), "r");
    ck_assert_ptr_nonnull(stream);

    int rc = scan_film(stream, &film);
    fclose(stream);

    ck_assert_int_ne(rc, OK);
    ck_assert_ptr_null(film);
}
END_TEST

START_TEST(scan_film_successful)
{
    char data[] = "title\nname\n2020\n";
    film_t *film = NULL;

    FILE *stream = fmemopen(data, strlen(data), "r");
    ck_assert_ptr_nonnull(stream);

    int rc = scan_film(stream, &film);
    fclose(stream);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_nonnull(film);
    ck_assert_str_eq(film->title, "title");
    ck_assert_str_eq(film->name, "name");
    ck_assert_int_eq(film->year, 2020);
    free_film(film);
}
END_TEST

START_TEST(read_films_from_unexisting_file)
{
    film_t **films_arr = NULL;
    int n = read_films_from_file("func_tests/xxx", 0, &films_arr);

    ck_assert_int_lt(n, 1);
    ck_assert_ptr_null(films_arr);
}
END_TEST

START_TEST(read_films_from_empty_file)
{
    film_t **films_arr = NULL;
    int n = read_films_from_file("func_tests/neg_04_in.txt", 0, &films_arr);

    ck_assert_int_lt(n, 1);
    ck_assert_ptr_null(films_arr);
}
END_TEST

START_TEST(read_films_from_invalid_file)
{
    film_t **films_arr = NULL;
    int n = read_films_from_file("func_tests/neg_05_in.txt", 0, &films_arr);

    ck_assert_int_lt(n, 1);
    ck_assert_ptr_null(films_arr);
}
END_TEST

START_TEST(read_films_from_valid_file)
{
    film_t **films_arr = NULL;
    int n = read_films_from_file("func_tests/pos_08_in.txt", 0, &films_arr);

    ck_assert_int_gt(n, 0);
    ck_assert_ptr_nonnull(films_arr);
    free_films_array(films_arr, n);
}
END_TEST

START_TEST(test_comapres)
{
    film_t a = {
        .title = "title A",
        .name = "name B",
        .year = 2020,
    };

    film_t b = {
        .title = "title B",
        .name = "name A",
        .year = 2020,
    };

    film_t *p_a = &a;
    film_t *p_b = &b;

    ck_assert_int_eq(cmp_films_by_title(&p_a, &p_b), -1);
    ck_assert_int_eq(cmp_films_by_name(&p_a, &p_b), 1);
    ck_assert_int_eq(cmp_films_by_year(&p_a, &p_b), 0);
}
END_TEST

START_TEST(test_print)
{
    film_t a = {
        .title = "title A",
        .name = "name B",
        .year = 2020,
    };

    film_t *p_a = &a;

    FILE *tmp = stdout;
    char *buf_p = NULL;
    size_t size = 0;
    stdout = open_memstream(&buf_p, &size);
    ck_assert_ptr_nonnull(stdout);

    print_films_array(&p_a, 1);
    fflush(stdout);
    fclose(stdout);
    stdout = tmp;

    ck_assert_ptr_nonnull(buf_p);
    ck_assert_str_eq(buf_p, "title A\nname B\n2020\n");
    free(buf_p);
}
END_TEST

Suite *film_array_suit(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("film_array");

    tc_neg = tcase_create("negatives");
    // tcase_add_test(tc_neg, scan_film_from_empty_stream);
    // tcase_add_test(tc_neg, scan_film_with_empty_title);
    // tcase_add_test(tc_neg, scan_film_with_empty_name);
    // tcase_add_test(tc_neg, scan_film_with_empty_year);
    // tcase_add_test(tc_neg, scan_film_with_empty_neg_year);
    tcase_add_test(tc_neg, read_films_from_unexisting_file);
    tcase_add_test(tc_neg, read_films_from_empty_file);
    tcase_add_test(tc_neg, read_films_from_invalid_file);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // tcase_add_test(tc_pos, scan_film_successful);
    tcase_add_test(tc_pos, read_films_from_valid_file);
    tcase_add_test(tc_pos, test_comapres);
    tcase_add_test(tc_pos, test_print);
    suite_add_tcase(s, tc_pos);

    return s;
}
