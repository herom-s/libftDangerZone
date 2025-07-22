#include "munit.h"
#include "libft.h"
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static MunitResult test_ft_memset_small(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	*s = malloc(10 + 1);
	munit_assert_memory_equal(10, memset(s, 'a', 10), ft_memset(s, 'a', 10));
    return MUNIT_OK;
}

static MunitResult test_ft_memset_neg_number(const MunitParameter params[], void* data) {

    (void) params;
    (void) data;
	char	*s = malloc(10 + 1);
	munit_assert_memory_equal(10, memset(s, -5, 10), ft_memset(s, -5, 10));
    return MUNIT_OK;
}

static MunitResult test_ft_memset_0_size(const MunitParameter params[], void* data) {

    (void) params;
    (void) data;
	char	*s = malloc(10 + 1);
	munit_assert_memory_equal(10, memset(s, 0, 0), ft_memset(s, 0, 0));
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_memset[] = {
    { "/mem_small", test_ft_memset_small, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/mem_neg_number", test_ft_memset_neg_number, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/mem_0_size", test_ft_memset_0_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* String test suite */
const MunitSuite test_suite_ft_memset = {
    "/test_ft_memset",
    tests_ft_memset,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
