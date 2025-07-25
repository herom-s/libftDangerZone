#include "munit.h"
#include "libft.h"
#include <limits.h>

static MunitResult test_ft_strncmp_simple_cmp(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[5] = "ABCD";
	char	s2[5] = "ABCD";
	munit_assert_int(strncmp(s1, s2, 5), ==,ft_strncmp(s1, s2, 5));
    return MUNIT_OK;
}

static MunitResult test_ft_strncmp_n_zero(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[5] = "ABCD";
	char	s2[5] = "ABCD";
	munit_assert_int(strncmp(s1, s2, 0), ==,ft_strncmp(s1, s2, 0));
    return MUNIT_OK;
}

static MunitResult test_ft_strncmp_only_1(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[5] = "ABCD";
	char	s2[5] = "ABCD";
	munit_assert_int(strncmp(s1, s2, 1), ==,ft_strncmp(s1, s2, 1));
    return MUNIT_OK;
}

static MunitResult test_ft_strncmp_n_too_big(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[5] = "ABCD";
	char	s2[5] = "ABCD";
	munit_assert_int(strncmp(s1, s2, 10), ==,ft_strncmp(s1, s2, 10));
    return MUNIT_OK;
}

static MunitResult test_ft_strncmp_s1_small_in_s2_big(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[5] = "ABCF";
	char	s2[5] = "ABCD";
	munit_assert_int(strncmp(s1, s2, 3), ==,ft_strncmp(s1, s2, 3));
    return MUNIT_OK;
}

static MunitResult test_ft_strncmp_s2_empty_n_equal_s1(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[5] = "ABCD";
	munit_assert_int(strncmp(s1, "", 5), ==,ft_strncmp(s1, "", 5));
    return MUNIT_OK;
}

static MunitResult test_ft_strncmp_s2_empty_n_zero(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[5] = "ABCD";
	munit_assert_int(strncmp(s1, "", 0), ==,ft_strncmp(s1, "", 5));
    return MUNIT_OK;
}

static MunitResult test_ft_strncmp_s1_too_small_n_equal_s2(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[3] = "AB";
	char	s2[5] = "ABCD";
	munit_assert_int(strncmp(s1, s2, 5), ==,ft_strncmp(s1, s2, 5));
    return MUNIT_OK;
}

static MunitResult test_ft_strncmp_s2_too_small_n_equal_s1(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	char	s1[5] = "ABCD";
	char	s2[3] = "AB";
	munit_assert_int(strncmp(s1, s2, 3), ==,ft_strncmp(s1, s2, 3));
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_strncmp[] = {
    { "/simple_cmp", test_ft_strncmp_simple_cmp, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/n_zero", test_ft_strncmp_n_zero, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/only_1", test_ft_strncmp_only_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/n_too_big", test_ft_strncmp_n_too_big, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/s1_small_in_s2_big", test_ft_strncmp_s1_small_in_s2_big, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/s2_empty_n_equal_s1", test_ft_strncmp_s2_empty_n_equal_s1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/s1_too_small_n_equal_s2", test_ft_strncmp_s1_too_small_n_equal_s2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/s2_too_small_n_equal_s1", test_ft_strncmp_s2_too_small_n_equal_s1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* String test suite */
const MunitSuite test_suite_ft_strncmp = {
    "/test_ft_strncmp",
    tests_ft_strncmp,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
