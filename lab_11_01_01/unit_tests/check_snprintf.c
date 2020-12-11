#include "../inc/check_snprintf.h"

START_TEST(snprintf_null)
{
    int rc = snprintf(NULL, 0, " ");
    int my_rc = my_snprintf(NULL, 0, " ");
    ck_assert_int_eq(rc, my_rc);
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("film_array");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, snprintf_null);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // tcase_add_test(tc_pos, test_comapres);
    suite_add_tcase(s, tc_pos);

    return s;
}
