#include "../inc/check_matrix_grow.h"

START_TEST(test_grow_one_element_matrix)
{
    int data[] = { 1 };

    matrix_t m = {
        .data = data,
        .width = 1,
        .height = 1,
    };

    int result_data[] = { 1, 1, 1,
                          1, 1, 1,
                          1, 1, 1 };

    matrix_t *r = grow_matrix(&m, 3);

    ck_assert_ptr_nonnull(r);
    ck_assert(r->width == 3);
    ck_assert(r->height == 3);
    ck_assert(memcmp(r->data, result_data, 9 * sizeof(int)) == 0);

    free_matrix(r);
}
END_TEST

START_TEST(test_grow_matrix)
{
    int data[] = { 1, 1,
                   -1, 4 };

    matrix_t m = {
        .data = data,
        .width = 2,
        .height = 2,
    };

    int result_data[] = { 1, 1, 1,
                          -1, 4, -1,
                          0, 2, 0 };

    matrix_t *r = grow_matrix(&m, 3);

    ck_assert_ptr_nonnull(r);
    ck_assert(r->width == 3);
    ck_assert(r->height == 3);
    ck_assert(memcmp(r->data, result_data, 9 * sizeof(int)) == 0);

    free_matrix(r);
}
END_TEST

Suite* matrix_grow_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("matrix_grow");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_grow_one_element_matrix);
    tcase_add_test(tc_pos, test_grow_matrix);
    suite_add_tcase(s, tc_pos);

    return s;
}
