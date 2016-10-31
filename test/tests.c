#include <stdbool.h>

#include "minunit.h"

#include "ratnum.h"

mpq_t a, b, c, expected;

int mpq_test_eq (mpq_t expected, mpq_t actual)
{
        if (!mpq_equal(expected, actual)) {
                char *ex = mpq_get_str(NULL, 10, expected);
                char *ac = mpq_get_str(NULL, 10, actual);
                log_err("expected: %s, actual: %s", ex, ac);
                free(ex);
                free(ac);
                return false;
        }
        return true;
}

char *test_add()
{
        mpq_set_si(expected, 3, 10);
        mpq_set_si(a, 1, 5);
        mpq_set_si(b, 1, 10);
        mpq_add(c, a, b);
        mu_assert(mpq_test_eq(expected, c), "not equal");
        return NULL;
}

char *all_tests()
{
        mu_suite_start();

        mu_run_test(test_add);

        return NULL;
}

RUN_TESTS(all_tests);
