#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define OK 1
#define FAILED 0

char* my_strrchr(const char *s, int c)
{
    const char *i = NULL;
    while (*s != '\0')
    {
        if (*s == c)
            i = s;
        s++;
    }
    if (*s == c)
        return (char *) s;
    return (char *) i;
}

int test(const char *s, int c, int test_n)
{
    char *target_result = strrchr(s, c);
    char *my_result = my_strrchr(s, c);
    if (my_result == target_result)
    {
        printf("Test%2d - passed\n", test_n);
        return OK;
    }
    else
    {
        printf("Test%2d - failed:\n", test_n);
        printf("  s: \"%s\"\n", s);
        printf("  c: '%c'\n", c);
        printf("  target: %d\n", (int) (target_result - s));
        printf("  result: %d\n", (int) (my_result - s));
        return FAILED;
    }
}

int main(void)
{
    int sum_passed = 0;
    int n = 0;

    sum_passed += test("", '1', ++n);
    sum_passed += test("a", '1', ++n);
    sum_passed += test("baa", 'a', ++n);
    sum_passed += test("baa", 'b', ++n);
    sum_passed += test("baa", '\0', ++n);

    printf("passed %d/%d\n", sum_passed, n);
}
