#include "../inc/check_main.h"

int main(void)
{
    SRunner *runner;

    runner = srunner_create(matrix_cut_suite());
    srunner_add_suite(runner, matrix_grow_suite());

    srunner_run_all(runner, CK_VERBOSE);

    int n_failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (n_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
