#include "../inc/check_snprintf.h"

START_TEST(snprintf_null)
{
    ck_assert_int_eq(
        snprintf(NULL, 0, " "),
        my_snprintf(NULL, 0, " "));
}
END_TEST

START_TEST(snprintf_text)
{
    char s1[8] = "", s2[8] = "";

    ck_assert_int_eq(
        snprintf(s1, 8, "bla bla"),
        my_snprintf(s2, 8, "bla bla"));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_char)
{
    char s1[2] = "", s2[2] = "";

    ck_assert_int_eq(
        snprintf(s1, 2, "%c", 'A'),
        my_snprintf(s2, 2, "%c", 'A'));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_char_null)
{
    ck_assert_int_eq(
        snprintf(NULL, 0, "%c", 'A'),
        my_snprintf(NULL, 0, "%c", 'A'));
}
END_TEST

START_TEST(snprintf_char_and_other)
{
    char s1[5] = "", s2[5] = "";

    ck_assert_int_eq(
        snprintf(NULL, 0, " 12%c", 'X'),
        my_snprintf(NULL, 0, " 12%c", 'X'));

    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_hex)
{
    char s1[2] = "", s2[2] = "";

    ck_assert_int_eq(
        snprintf(s1, 2, "%x", 15),
        my_snprintf(s2, 2, "%x", 15));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_hex_overflow)
{
    char s1[2] = "", s2[2] = "";
    int i = 16;

    ck_assert_int_eq(
        snprintf(s1, 2, "%x", i),
        my_snprintf(s2, 2, "%x", i));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_hex_two_chars)
{
    char s1[3] = "", s2[3] = "";
    int i = 24;

    ck_assert_int_eq(
        snprintf(s1, 3, "%x", i),
        my_snprintf(s2, 3, "%x", i));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_hex_neg)
{
    char s1[4] = "", s2[4] = "";
    int i = -31;

    ck_assert_int_eq(
        snprintf(s1, 4, "%x", i),
        my_snprintf(s2, 4, "%x", i));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_hex_other)
{
    char s1[12] = "", s2[12] = "";
    int i = -31;

    ck_assert_int_eq(
        snprintf(s1, 12, "  0x%x  ", i),
        my_snprintf(s2, 12, "  0x%x  ", i));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_str)
{
    char s1[12] = "", s2[12] = "";
    char s[] = "hello";

    ck_assert_int_eq(
        snprintf(s1, 12, "%s", s),
        my_snprintf(s2, 12, "%s", s));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_str_zero)
{
    char s1[12] = "", s2[12] = "";
    char s[] = "";

    ck_assert_int_eq(
        snprintf(s1, 12, "%s", s),
        my_snprintf(s2, 12, "%s", s));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_str_overflow)
{
    char s1[12] = "", s2[12] = "";
    char s[] = "1234 hello world !!!!";

    ck_assert_int_eq(
        snprintf(s1, 12, "%s", s),
        my_snprintf(s2, 12, "%s", s));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_str_len)
{
    char s[] = "1234 hello world !!!!";

    ck_assert_int_eq(
        snprintf(NULL, 0, "%s", s),
        my_snprintf(NULL, 0, "%s", s));
}
END_TEST

START_TEST(snprintf_str_other)
{
    char s1[12] = "", s2[12] = "";
    char s[] = "hello world !!!!";

    ck_assert_int_eq(
        snprintf(s1, 12, "1234 %s", s),
        my_snprintf(s2, 12, "%s", s));
    ck_assert_str_eq(s1, s2);
}
END_TEST


START_TEST(snprintf_longhex)
{
    char s1[20] = "", s2[20] = "";
    unsigned long i = ULONG_MAX;

    ck_assert_int_eq(
        snprintf(s1, 20, "%lx", i),
        my_snprintf(s2, 20, "%lx", i));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_shorthex)
{
    char s1[20] = "", s2[20] = "";
    unsigned short i = USHRT_MAX;

    ck_assert_int_eq(
        snprintf(s1, 20, "%hx", i),
        my_snprintf(s2, 20, "%hx", i));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_big_combo)
{
    char s1[128] = "", s2[128] = "";
    char c = 'X';
    int i = 10;
    char s[] = "world";
    unsigned long l = ULONG_MAX;
    unsigned short h = USHRT_MAX;

    ck_assert_int_eq(
        snprintf(s1, 128, "%c %x %s %lx %hx", c, i, s, l, h),
        my_snprintf(s2, 128, "%c %x %s %lx %hx", c, i, s, l, h));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(snprintf_big_combo_len)
{
    char c = 'X';
    int i = 10;
    char s[] = "world";
    unsigned long l = ULONG_MAX;
    unsigned short h = USHRT_MAX;

    ck_assert_int_eq(
        snprintf(NULL, 0, "%c %x %s %lx %hx", c, i, s, l, h),
        my_snprintf(NULL, 0, "%c %x %s %lx %hx", c, i, s, l, h));
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
    tcase_add_test(tc_pos, snprintf_text);
    tcase_add_test(tc_pos, snprintf_char);
    tcase_add_test(tc_pos, snprintf_char_null);
    tcase_add_test(tc_pos, snprintf_char_and_other);
    tcase_add_test(tc_pos, snprintf_hex);
    tcase_add_test(tc_pos, snprintf_hex_overflow);
    tcase_add_test(tc_pos, snprintf_hex_two_chars);
    tcase_add_test(tc_pos, snprintf_hex_neg);
    tcase_add_test(tc_pos, snprintf_hex_other);
    tcase_add_test(tc_pos, snprintf_str);
    tcase_add_test(tc_pos, snprintf_str_zero);
    tcase_add_test(tc_pos, snprintf_str_overflow);
    tcase_add_test(tc_pos, snprintf_str_len);
    tcase_add_test(tc_pos, snprintf_str_other);
    tcase_add_test(tc_pos, snprintf_longhex);
    tcase_add_test(tc_pos, snprintf_shorthex);
    tcase_add_test(tc_pos, snprintf_big_combo);
    tcase_add_test(tc_pos, snprintf_big_combo_len);
    suite_add_tcase(s, tc_pos);

    return s;
}
