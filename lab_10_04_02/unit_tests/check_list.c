#include "../inc/check_list.h"

node_t *create_list(int n, ...)
{
    node_t *head = NULL, *tail = NULL;
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; i++)
    {
        node_t *p = malloc(sizeof(node_t));

        if (!p)
        {
            APPEND(head, tail, NULL);
            free_list(head, NULL);
            return NULL;
        }

        p->data = va_arg(args, void *);

        APPEND(head, tail, p);
    }

    APPEND(head, tail, NULL);

    va_end(args);

    return head;
}

int cmp_int(const void *a, const void *b)
{
    int ai = *((int *) a);
    int bi = *((int *) b);
    return ai < bi ? -1 : ai == bi ? 0 : 1;
}

START_TEST(pop_front_empty)
{
    node_t *head = NULL;
    ck_assert_ptr_null(pop_front(&head));
    ck_assert_ptr_null(head);
}
END_TEST

START_TEST(pop_front_two_elems)
{
    int data, data2;
    node_t *l = create_list(2, &data, &data2);
    ck_assert_ptr_nonnull(l);

    ck_assert_ptr_eq(pop_front(&l), &data);
    ck_assert_ptr_eq(pop_front(&l), &data2);
    ck_assert_ptr_null(pop_front(&l));
    ck_assert_ptr_null(l);
}
END_TEST

START_TEST(find_null)
{
    ck_assert_ptr_null(find(NULL, NULL, NULL));
}
END_TEST

START_TEST(find_check)
{
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    node_t *l = create_list(3, &i1, &i2, &i3);
    ck_assert_ptr_nonnull(l);

    ck_assert_ptr_eq(find(l, &i1, cmp_int)->data, &i1);
    ck_assert_ptr_eq(find(l, &i2, cmp_int)->data, &i2);
    ck_assert_ptr_eq(find(l, &i3, cmp_int)->data, &i3);
    ck_assert_ptr_null(find(l, &i4, cmp_int));
    free_list(l, NULL);
}
END_TEST

START_TEST(reverse_check)
{
    int i1 = 1, i2 = 2, i3 = 3;
    node_t *l = create_list(3, &i1, &i2, &i3);
    ck_assert_ptr_nonnull(l);

    l = reverse(l);
    ck_assert_ptr_eq(pop_front(&l), &i3);

    l = reverse(l);
    ck_assert_ptr_eq(pop_front(&l), &i1);

    l = reverse(l);
    ck_assert_ptr_eq(pop_front(&l), &i2);

    l = reverse(l);
    ck_assert_ptr_null(pop_front(&l));
    ck_assert_ptr_null(l);
}
END_TEST

START_TEST(front_back_split_even)
{
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    node_t *l = create_list(4, &i1, &i2, &i3, &i4);
    ck_assert_ptr_nonnull(l);

    node_t *l2 = NULL;

    front_back_split(l, &l2);
    ck_assert_ptr_nonnull(l2);

    ck_assert_ptr_eq(pop_front(&l), &i1);
    ck_assert_ptr_eq(pop_front(&l), &i2);
    ck_assert_ptr_eq(pop_front(&l2), &i3);
    ck_assert_ptr_eq(pop_front(&l2), &i4);
    ck_assert_ptr_null(pop_front(&l));
    ck_assert_ptr_null(pop_front(&l2));
    ck_assert_ptr_null(l);
    ck_assert_ptr_null(l2);
}
END_TEST

START_TEST(front_back_split_odd)
{
    int i1 = 1, i2 = 2, i3 = 3;
    node_t *l = create_list(3, &i1, &i2, &i3);
    ck_assert_ptr_nonnull(l);

    node_t *l2 = NULL;

    front_back_split(l, &l2);
    ck_assert_ptr_nonnull(l2);

    ck_assert_ptr_eq(pop_front(&l), &i1);
    ck_assert_ptr_eq(pop_front(&l), &i2);
    ck_assert_ptr_eq(pop_front(&l2), &i3);
    ck_assert_ptr_null(pop_front(&l));
    ck_assert_ptr_null(pop_front(&l2));
    ck_assert_ptr_null(l);
    ck_assert_ptr_null(l2);
}
END_TEST

START_TEST(front_back_split_empty)
{
    node_t *l;
    front_back_split(NULL, &l);
    ck_assert_ptr_null(l);
}
END_TEST

START_TEST(front_back_split_null_back)
{
    front_back_split(NULL, NULL);
}
END_TEST

START_TEST(sorted_merge_null)
{
    sorted_merge(NULL, NULL, NULL);
}
END_TEST

START_TEST(sorted_merge_empty)
{
    node_t *l1 = NULL;
    node_t *l2 = NULL;
    node_t *l = sorted_merge(&l1, &l2, cmp_int);

    ck_assert_ptr_null(l);
}
END_TEST

START_TEST(sorted_merge_one_empty)
{
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    node_t *l1 = create_list(4, &i1, &i2, &i3, &i4);
    ck_assert_ptr_nonnull(l1);

    node_t *l2 = NULL;
    node_t *l = sorted_merge(&l1, &l2, cmp_int);

    ck_assert_ptr_nonnull(l);
    ck_assert_ptr_null(l1);
    ck_assert_ptr_null(l2);
    ck_assert_ptr_eq(pop_front(&l), &i1);
    ck_assert_ptr_eq(pop_front(&l), &i2);
    ck_assert_ptr_eq(pop_front(&l), &i3);
    ck_assert_ptr_eq(pop_front(&l), &i4);
    ck_assert_ptr_null(pop_front(&l));
    ck_assert_ptr_null(l);
}
END_TEST

START_TEST(sorted_merge_check)
{
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;
    node_t *l1 = create_list(3, &i2, &i3, &i4);
    ck_assert_ptr_nonnull(l1);
    node_t *l2 = create_list(4, &i1, &i2, &i4, &i5);
    ck_assert_ptr_nonnull(l2);

    node_t *l = sorted_merge(&l1, &l2, cmp_int);

    ck_assert_ptr_nonnull(l);
    ck_assert_ptr_null(l1);
    ck_assert_ptr_null(l2);
    ck_assert_ptr_eq(pop_front(&l), &i1);
    ck_assert_ptr_eq(pop_front(&l), &i2);
    ck_assert_ptr_eq(pop_front(&l), &i2);
    ck_assert_ptr_eq(pop_front(&l), &i3);
    ck_assert_ptr_eq(pop_front(&l), &i4);
    ck_assert_ptr_eq(pop_front(&l), &i4);
    ck_assert_ptr_eq(pop_front(&l), &i5);
    ck_assert_ptr_null(pop_front(&l));
    ck_assert_ptr_null(l);
}
END_TEST

START_TEST(sort_check)
{
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    node_t *l = create_list(4, &i3, &i2, &i4, &i1);
    ck_assert_ptr_nonnull(l);

    l = sort(l, cmp_int);

    ck_assert_ptr_nonnull(l);
    ck_assert_ptr_eq(pop_front(&l), &i1);
    ck_assert_ptr_eq(pop_front(&l), &i2);
    ck_assert_ptr_eq(pop_front(&l), &i3);
    ck_assert_ptr_eq(pop_front(&l), &i4);
    ck_assert_ptr_null(pop_front(&l));
    ck_assert_ptr_null(l);
}
END_TEST

Suite *list_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("film_array");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, find_null);
    tcase_add_test(tc_neg, front_back_split_null_back);
    tcase_add_test(tc_neg, sorted_merge_null);
    // tcase_add_test(tc_neg, pop_front_invalid_head);
    // tcase_add_test(tc_neg, scan_film_with_empty_title);
    // tcase_add_test(tc_neg, scan_film_with_empty_name);
    // tcase_add_test(tc_neg, scan_film_with_empty_year);
    // tcase_add_test(tc_neg, scan_film_with_empty_neg_year);
    // tcase_add_test(tc_neg, read_films_from_unexisting_file);
    // tcase_add_test(tc_neg, read_films_from_empty_file);
    // tcase_add_test(tc_neg, read_films_from_invalid_file);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, pop_front_empty);
    tcase_add_test(tc_pos, pop_front_two_elems);
    tcase_add_test(tc_pos, find_check);
    tcase_add_test(tc_pos, reverse_check);
    tcase_add_test(tc_pos, front_back_split_empty);
    tcase_add_test(tc_pos, front_back_split_even);
    tcase_add_test(tc_pos, front_back_split_odd);
    tcase_add_test(tc_pos, sorted_merge_empty);
    tcase_add_test(tc_pos, sorted_merge_one_empty);
    tcase_add_test(tc_pos, sorted_merge_check);
    tcase_add_test(tc_pos, sort_check);

    // tcase_add_test(tc_pos, read_films_from_valid_file);
    // tcase_add_test(tc_pos, test_comapres);
    suite_add_tcase(s, tc_pos);

    return s;
}
