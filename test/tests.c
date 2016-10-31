#include "minunit.h"

#include "ratnum.h"

mpq_t a, b, c, expected;

char *test_add()
{
        mpq_set_si(expected, 3, 10);
        mpq_set_si(a, 1, 5);
        mpq_set_si(b, 1, 10);
        mpq_add(c, a, b);
        mu_assert(mpq_cmp(expected, c) == 0, "not equal");
        return NULL;
}

char *all_tests()
{
        mu_suite_start();

        mu_run_test(test_add);

        return NULL;
}

RUN_TESTS(all_tests);
