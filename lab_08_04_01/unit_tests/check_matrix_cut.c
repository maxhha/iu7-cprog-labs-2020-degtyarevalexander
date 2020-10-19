#include "../inc/check_matrix_cut.h"

START_TEST(test_cut_square_matrix)
{
    int data[] = { 1, 2, 3, 4 };

    matrix_t m = {
        .data = data,
        .width = 2,
        .height = 2,
    };

    matrix_t *r = cut_matrix(&m);

    ck_assert_ptr_nonnull(r);
    ck_assert(r->width == 2);
    ck_assert(r->height == 2);
    ck_assert(memcmp(r->data, data, 4 * sizeof(int)) == 0);

    free_matrix(r);
}
END_TEST

START_TEST(test_cut_matrix_rows)
{
    int data[] = { 10, 0,
                   1, 5,
                   5, 1,
                   3, 4 };

    matrix_t m = {
        .data = data,
        .width = 2,
        .height = 4,
    };

    int result_data[] = {5, 1, 3, 4};

    matrix_t *r = cut_matrix(&m);

    ck_assert_ptr_nonnull(r);
    ck_assert(r->width == 2);
    ck_assert(r->height == 2);
    ck_assert(memcmp(r->data, result_data, 4 * sizeof(int)) == 0);

    free_matrix(r);
}
END_TEST

START_TEST(test_cut_matrix_columns)
{
    int data[] = { 10, 4, 1, 2,
                   5, 1, 3, 4 };

    matrix_t m = {
        .data = data,
        .width = 4,
        .height = 2,
    };

    int result_data[] = {4, 1, 1, 3};

    matrix_t *r = cut_matrix(&m);

    ck_assert_ptr_nonnull(r);
    ck_assert(r->width == 2);
    ck_assert(r->height == 2);
    ck_assert(memcmp(r->data, result_data, 4 * sizeof(int)) == 0);

    free_matrix(r);
}
END_TEST

Suite* matrix_cut_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("matrix_cut");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_cut_square_matrix);
    tcase_add_test(tc_pos, test_cut_matrix_rows);
    tcase_add_test(tc_pos, test_cut_matrix_columns);
    suite_add_tcase(s, tc_pos);

    return s;
}
