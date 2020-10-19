#include "../inc/check_matrix_mul.h"

START_TEST(test_multiply_matrix)
{
    int data_a[] = { 1, 0, 1,
                   0, -1, 0,
                   1, 2, 1 };

    matrix_t a = {
        .data = data_a,
        .width = 3,
        .height = 3,
    };

    int data_b[] = { 1, 2, 3,
                   5, 7, 11,
                   13, 17, 19 };

    matrix_t b = {
        .data = data_b,
        .width = 3,
        .height = 3,
    };

    int result_data[] = { 14, 19, 22,
                          -5, -7, -11,
                          24, 33, 44 };

    matrix_t *r = multiply_matrix(&a, &b);

    ck_assert_ptr_nonnull(r);
    ck_assert(r->width == 3);
    ck_assert(r->height == 3);
    ck_assert(memcmp(r->data, result_data, 9 * sizeof(int)) == 0);

    free_matrix(r);
}
END_TEST

START_TEST(test_get_matrix_power)
{
    int data[] = { 1, 0, 1,
                   0, -1, 0,
                   1, 2, 1 };

    matrix_t m = {
        .data = data,
        .width = 3,
        .height = 3,
    };

    int result_data[] = { 4, 2, 4,
                          0, -1, 0,
                          4, 4, 4 };

    matrix_t *r = get_matrix_power(&m, 3);

    ck_assert_ptr_nonnull(r);
    ck_assert(r->width == 3);
    ck_assert(r->height == 3);
    ck_assert(memcmp(r->data, result_data, 9 * sizeof(int)) == 0);

    free_matrix(r);
}
END_TEST

START_TEST(test_get_matrix_in_zero_power)
{
    int data[] = { 1, 0, 1,
                   0, -1, 0,
                   1, 2, 1 };

    matrix_t m = {
        .data = data,
        .width = 3,
        .height = 3,
    };

    int result_data[] = { 1, 0, 0,
                          0, 1, 0,
                          0, 0, 1 };

    matrix_t *r = get_matrix_power(&m, 0);

    ck_assert_ptr_nonnull(r);
    ck_assert(r->width == 3);
    ck_assert(r->height == 3);
    ck_assert(memcmp(r->data, result_data, 9 * sizeof(int)) == 0);

    free_matrix(r);
}
END_TEST

Suite* matrix_mul_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("matrix_mul");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_multiply_matrix);
    tcase_add_test(tc_pos, test_get_matrix_power);
    tcase_add_test(tc_pos, test_get_matrix_in_zero_power);
    suite_add_tcase(s, tc_pos);

    return s;
}
