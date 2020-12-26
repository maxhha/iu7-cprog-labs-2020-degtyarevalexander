#include "../inc/check_array.h"

START_TEST(test_read_array_from_empty_file)
{
    FILE *f = fopen("func_tests/neg_03_in.txt", "r");
    ck_assert_ptr_ne(f, NULL);

    int *b_array, *e_array;
    int rc = read_array(f, &b_array, &e_array);
    fclose(f);

    ck_assert_int_eq(rc, EREADARRAY);
}
END_TEST

START_TEST(test_key_null_pointers)
{
    int rc = key(NULL, NULL, NULL, NULL);
    ck_assert_int_eq(rc, EFILTERARRAY);
}
END_TEST

START_TEST(test_key_no_elements)
{
    int pb_data[] = {1, 2, 3};
    int *pe_data = pb_data + 3;
    int rc = key(pb_data, pe_data, NULL, NULL);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_key)
{
    int pb_data[] = {0, 1, 0, -6, 3, 1, 1};
    int *pe_data = pb_data + 7;
    int *pb_res = malloc(3 * sizeof(int)), *pe_res;
    ck_assert_ptr_nonnull(pb_res);

    ck_assert_int_eq(key(pb_data, pe_data, NULL, NULL), 3);
    ck_assert_int_eq(key(pb_data, pe_data, (int **) &pb_res, &pe_res), 3);

    int res[] = {1, 0, 3};
    int *e_res = res + 3;
    for (int *i = pb_res, *j = res; i < pe_res && i - pb_res < e_res - res; i++, j++)
        ck_assert_int_eq(*i, *j);
    free(pb_res);
}
END_TEST

START_TEST(test_key_null_end)
{
    int pb_data[] = {0, 1, 0, -6, 3, 1, 1};
    int *pe_data = pb_data + 7;
    int pb_res[4];

    ck_assert_int_eq(key(pb_data, pe_data, NULL, NULL), 3);
    ck_assert_int_eq(key(pb_data, pe_data, (int **) &pb_res, NULL), EFILTERARRAY);
}
END_TEST

Suite* array_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("array");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_read_array_from_empty_file);
    tcase_add_test(tc_neg, test_key_null_pointers);
    tcase_add_test(tc_neg, test_key_no_elements);
    tcase_add_test(tc_neg, test_key_null_end);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_key);
    suite_add_tcase(s, tc_pos);

    return s;
}
