#include <stdbool.h>

#include "minunit.h"

#include "ratnum.h"

Q_t a, b, c, expected;

int Q_test_eq (Q_t expected, Q_t actual)
{
        if (!Q_equal(expected, actual)) {
                char *ex = Q_get_str(expected, 10);
                char *ac = Q_get_str(actual, 10);
                log_err("expected: %s, actual: %s", ex, ac);
                free(ex);
                free(ac);
                return false;
        }
        return true;
}

char *test_canonicalize()
{
        expected = (Q_t) {-1, 2};
        a = (Q_t) {2, -4};
        Q_canonicalize(&a);
        mu_assert(Q_test_eq(expected, a), "not equal");

        expected = (Q_t) {1, 1};
        a = (Q_t) {-4, -4};
        Q_canonicalize(&a);
        mu_assert(Q_test_eq(expected, a), "not equal");

        expected = Q_zero;
        a = (Q_t) {0, -2};
        Q_canonicalize(&a);
        mu_assert(Q_test_eq(expected, a), "not equal");

        return NULL;
}

char *test_add()
{
        expected = (Q_t) {3, 10};
        a = (Q_t) {1, 5};
        b = (Q_t) {1, 10};
        c = Q_add(a, b);

        mu_assert(Q_test_eq(expected, c), "not equal");
        return NULL;
}

char *test_sub()
{
        expected = (Q_t) {1, 2};
        a = (Q_t) {3, 4};
        b = (Q_t) {1, 4};
        c = Q_sub(a, b);
        mu_assert(Q_test_eq(expected, c), "not equal");

        expected = Q_zero;
        a = (Q_t) {1, 1};
        b = (Q_t) {1, 1};
        c = Q_sub(a, b);
        mu_assert(Q_test_eq(expected, c), "not equal");
        return NULL;
}

char *test_mul()
{
        expected = (Q_t) {3, 8};
        a = (Q_t) {5, 8};
        b = (Q_t) {3, 5};

        mu_assert(Q_test_eq(expected, Q_mul(a, b)), "not equal");
        return NULL;
}

char *test_swap()
{
        a = (Q_t) {1, 2};
        b = (Q_t) {3, 4};

        Q_t tmp = a;
        a = b;
        b = tmp;

        mu_assert(Q_test_eq((Q_t) {3, 4}, a), "not equal");
        mu_assert(Q_test_eq((Q_t) {1, 2}, b), "not equal");
        return NULL;
}

char *test_str()
{
        char *s;

        a = (Q_t) {0};
        s = Q_get_str(a, 10);
        mu_assert_str_eq("NaN", s);
        free(s);

        a = (Q_t) {2, 1};
        s = Q_get_str(a, 10);
        mu_assert_str_eq("2", s);
        free(s);

        a = (Q_t) {3, 4};
        s = Q_get_str(a, 10);
        mu_assert_str_eq("3/4", s);
        free(s);

        return NULL;
}

char *all_tests()
{
        mu_suite_start();

        mu_run_test(test_add);
        mu_run_test(test_sub);
        mu_run_test(test_mul);
        mu_run_test(test_swap);
        mu_run_test(test_str);
        mu_run_test(test_canonicalize);

        return NULL;
}

RUN_TESTS(all_tests);
