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
    int *pb_res, *pe_res;
    int rc = key(pb_data, pe_data, &pb_res, &pe_res);
    ck_assert_int_eq(rc, EFILTERARRAY);
}
END_TEST

START_TEST(test_key)
{
    int pb_data[] = {0, 1, 0, -6, 3, 1, 1};
    int *pe_data = pb_data + 7;
    int *pb_res, *pe_res;
    int rc = key(pb_data, pe_data, &pb_res, &pe_res);
    ck_assert_int_eq(rc, OK);
    int res[] = {1, 0, 3, 1};
    int *e_res = res + 4;
    for (int *i = pb_res, *j = res; i < pe_res && i - pb_res < e_res - res; i++, j++)
        ck_assert_int_eq(*i, *j);
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
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_key);
    suite_add_tcase(s, tc_pos);

    return s;
}
