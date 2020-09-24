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

Suite* array_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    // TCase *tc_pos;

    s = suite_create("array");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_read_array_from_empty_file);
    suite_add_tcase(s, tc_neg);

    // tc_pos = tcase_create("positives");
    // tcase_add_test(tc_pos, test_calc_avg_array_with_one_element);

    // suite_add_tcase(s, tc_pos);

    return s;
}
