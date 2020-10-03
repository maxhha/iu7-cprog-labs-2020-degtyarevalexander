#include "../inc/check_main.h"

int main(void)
{
    int no_failed = 0;
    Suite *s_array, *s_mysort;
    SRunner *runner;

    s_array = array_suite();
    s_mysort = mysort_suite();

    runner = srunner_create(s_array);
    srunner_add_suite(runner, s_mysort);

    srunner_run_all(runner, CK_VERBOSE);

    no_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
