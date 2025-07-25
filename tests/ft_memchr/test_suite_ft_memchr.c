#include "munit.h"
#include "libft.h"
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdlib.h>

static MunitResult test_ft_memchr_base(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[] = "caos";
	char	*res1 = memchr(s1, 'o', 3);
	char	*res2 = ft_memchr(s1, 'o', 3);
	munit_assert_ptr_equal(res1, res2);
    return MUNIT_OK;
}

static MunitResult test_ft_memchr_c_not_in_s(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[] = "caos";
	char	*res1 = memchr(s1, 'v', 5);
	char	*res2 = ft_memchr(s1, 'v', 5);
	munit_assert_ptr_equal(res1, res2);
    return MUNIT_OK;
}

static MunitResult test_ft_memchr_c_is_neg(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	int		s1[] = {1, 2, 3, -5, 2};
	char	*res1 = memchr(s1, -5, 5);
	char	*res2 = ft_memchr(s1, -5, 5);
	munit_assert_ptr_equal(res1, res2);
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_memchr[] = {
    { "/base", test_ft_memchr_base, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/c_not_in_s", test_ft_memchr_c_not_in_s, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/c_is_neg", test_ft_memchr_c_is_neg, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* String test suite */
const MunitSuite test_suite_ft_memchr = {
    "/test_ft_memchr",
    tests_ft_memchr,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
