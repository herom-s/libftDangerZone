#include "munit.h"
#include "libft.h"
#include <ctype.h>

static MunitResult test_ft_toupper_lowercase(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    // Test all lowercase letters
    for (int c = 'a'; c <= 'z'; c++) {
        munit_assert_int(toupper(c), ==, ft_toupper(c));
    }
    return MUNIT_OK;
}

static MunitResult test_ft_toupper_uppercase(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    // Test all uppercase letters (should remain unchanged)
    for (int c = 'A'; c <= 'Z'; c++) {
        munit_assert_int(toupper(c), ==, ft_toupper(c));
    }
    return MUNIT_OK;
}

static MunitResult test_ft_toupper_digits(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    // Test digits (should remain unchanged)
    for (int c = '0'; c <= '9'; c++) {
        munit_assert_int(toupper(c), ==, ft_toupper(c));
    }
    return MUNIT_OK;
}

static MunitResult test_ft_toupper_special_chars(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    // Test various special characters
    int special_chars[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', 
                          '-', '_', '=', '+', '[', ']', '{', '}', '\\', '|', 
                          ';', ':', '"', '\'', '<', '>', ',', '.', '?', '/', 
                          '`', '~', ' ', '\t', '\n'};
    
    int num_chars = sizeof(special_chars) / sizeof(special_chars[0]);
    
    for (int i = 0; i < num_chars; i++) {
        int c = special_chars[i];
        munit_assert_int(toupper(c), ==, ft_toupper(c));
    }
    return MUNIT_OK;
}

static MunitResult test_ft_toupper_extended_ascii(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    // Test extended ASCII characters
    for (int c = 128; c < 256; c++) {
        munit_assert_int(toupper(c), ==, ft_toupper(c));
    }
    return MUNIT_OK;
}

static MunitResult test_ft_toupper_control_chars(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    // Test control characters (0-31, 127)
    for (int c = 0; c < 32; c++) {
        munit_assert_int(toupper(c), ==, ft_toupper(c));
    }
    munit_assert_int(toupper(127), ==, ft_toupper(127));
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_toupper[] = {
    { "/lowercase", test_ft_toupper_lowercase, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/uppercase", test_ft_toupper_uppercase, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/digits", test_ft_toupper_digits, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/special_chars", test_ft_toupper_special_chars, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/extended_ascii", test_ft_toupper_extended_ascii, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/control_chars", test_ft_toupper_control_chars, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Test suite */
const MunitSuite test_suite_ft_toupper = {
    "/test_ft_toupper",
    tests_ft_toupper,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
