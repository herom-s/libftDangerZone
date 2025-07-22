#include "munit.h"
#include "libft.h"
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

static MunitResult test_ft_isprint_lowercase_alpha(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	for (int i = 'a'; i <= 'z'; i++) {
		munit_assert_int(isprint(i) != 0, ==,ft_isprint(i) != 0);
	}
    return MUNIT_OK;
}

static MunitResult test_ft_isprint_uppercase_alpha(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	for (int i = 'A'; i <= 'Z'; i++) {
		munit_assert_int(isprint(i) != 0, ==,ft_isprint(i) != 0);
	}
    return MUNIT_OK;
}

static MunitResult test_ft_isprint_digit(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	for (int i = '0'; i <= '9'; i++) {
		munit_assert_int(isprint(i) != 0, ==,ft_isprint(i) != 0);
	}
    return MUNIT_OK;
}

static MunitResult test_ft_isprint_print(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	for (int i = ' '; i <= '~'; i++) {
		munit_assert_int(isprint(i) != 0, ==, ft_isprint(i) != 0);
	}
    return MUNIT_OK;
}

static MunitResult test_ft_isprint_non_print(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	for (int i = 0; i <= 31; i++) {
		munit_assert_int(isprint(i), ==, ft_isprint(i));
	}
	munit_assert_int(isprint(127), ==, ft_isprint(127));
    return MUNIT_OK;
}

static MunitResult test_ft_isprint_ascii(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	for (int i = 0; i <= 127; i++) {
		munit_assert_int(isprint(i) != 0, ==, ft_isprint(i) != 0);
	}
    return MUNIT_OK;
}

static MunitResult test_ft_isprint_extend_ascii(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	for (int i = 128; i <= 255; i++) {
		munit_assert_int(isprint(i), ==, ft_isprint(i));
	}
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_isprint[] = {
    { "/lowercase", test_ft_isprint_lowercase_alpha, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/uppercase", test_ft_isprint_uppercase_alpha, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/digit", test_ft_isprint_digit, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/print", test_ft_isprint_print, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/non_print", test_ft_isprint_non_print, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/ascii", test_ft_isprint_ascii, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/extended_ascii", test_ft_isprint_extend_ascii, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* String test suite */
const MunitSuite test_suite_ft_isprint = {
    "/test_ft_isprint",
    tests_ft_isprint,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
