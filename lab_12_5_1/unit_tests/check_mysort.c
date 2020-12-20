#include "../inc/check_mysort.h"

START_TEST(test_sort)
{
    #define SUBARRAY_SIZE 20
    int *pb_array, *pe_array;
    int rc = read_array_from_file("func_tests/pos_06_in.txt", &pb_array, &pe_array);

    ck_assert_int_eq(rc, OK);

    for (int *i = pb_array; i + SUBARRAY_SIZE <= pe_array; i += SUBARRAY_SIZE)
    {
        int data_mysort[SUBARRAY_SIZE];
        int data_qsort[SUBARRAY_SIZE];
        memcpy(data_mysort, i, SUBARRAY_SIZE * sizeof(int));
        memcpy(data_qsort, i, SUBARRAY_SIZE * sizeof(int));
        mysort(data_mysort, SUBARRAY_SIZE, sizeof(int), compare_numbers);
        qsort(data_qsort, SUBARRAY_SIZE, sizeof(int), compare_numbers);

        if (memcmp(data_mysort, data_qsort, SUBARRAY_SIZE * sizeof(int)) != 0)
        {

            LOG_INFO("%s", "Error on sort arrays");
            LOG_INFO("%s", "mysort:");

            for (int *j = data_mysort; j < data_mysort + SUBARRAY_SIZE; j++)
                LOG_INFO("%d", *j);

            LOG_INFO("%s", "qsort:");

            for (int *j = data_qsort; j < data_qsort + SUBARRAY_SIZE; j++)
                LOG_INFO("%d", *j);

            free(pb_array);
            ck_abort_msg("Error on sort of %d:%d", (int) (i - pb_array), (int) (i - pb_array) + SUBARRAY_SIZE);
        }
    }

    free(pb_array);

    #undef SUBARRAY_SIZE
}
END_TEST

Suite* mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("mysort");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sort);

    suite_add_tcase(s, tc_pos);

    return s;
}
