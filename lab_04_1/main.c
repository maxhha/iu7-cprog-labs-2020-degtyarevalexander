#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my_string.h"

#define BEGIN_TEST(RESULT_T, F) \
    { \
        RESULT_T _r; \
        RESULT_T _my_r; \
        __typeof__ (__typeof__ (F) * ) _f = &F; \
        __typeof__ (_f) _my_f = &my_ ## F; \
        int sum = 0, n = 0; \
        printf("Testing " #F ":\n");

#define TEST(...) \
        _r = _f(__VA_ARGS__); \
        _my_r = _my_f(__VA_ARGS__); \
        printf("Test%d - %s\n", ++n, _r == _my_r ? "pass" : "fail"); \
        sum += _r == _my_r;

#define END_TEST(F) \
        printf(#F ": passed %d/%d\n", sum, n); \
    }

int main(void)
{
    BEGIN_TEST (char *, strpbrk);
    TEST ("", "1");
    TEST ("a", "1");
    TEST ("baa", "1");
    TEST ("baa", "b");
    TEST ("baa", "\0");
    TEST ("aabaacaa", "bc");
    END_TEST (strpbrk);

    printf("\n");

    BEGIN_TEST (size_t, strspn);
    TEST ("", "");
    TEST ("", "b");
    TEST ("baba", "");
    TEST ("baba", "b");
    TEST ("baba", "a");
    TEST ("baba", "ba");
    TEST ("babac", "ba");
    END_TEST (strspn);

    printf("\n");

    BEGIN_TEST (size_t, strcspn);
    TEST ("", "");
    TEST ("", "b");
    TEST ("baba", "");
    TEST ("baba", "b");
    TEST ("baba", "a");
    TEST ("baba", "ba");
    TEST ("cbaba", "ba");
    END_TEST (strcspn);

    printf("\n");

    BEGIN_TEST (char *, strchr);
    TEST ("", '1');
    TEST ("a", '1');
    TEST ("ab", '1');
    TEST ("ab", 'a');
    TEST ("ab", 'b');
    TEST ("baa", 'a');
    TEST ("baa", '\0');
    END_TEST (strrchr);

    printf("\n");

    BEGIN_TEST (char *, strrchr);
    TEST ("", '1');
    TEST ("a", '1');
    TEST ("ab", '1');
    TEST ("ab", 'a');
    TEST ("ab", 'b');
    TEST ("baa", 'a');
    TEST ("baa", '\0');
    END_TEST (strrchr);
}
