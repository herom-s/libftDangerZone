#include "munit.h"
#include "libft.h"
#include <bsd/string.h>
#include <stdlib.h>

static MunitResult test_ft_strlcpy_normal(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "Hello";
    char dest1[10];
    char dest2[10];
    size_t result1, result2;
    
    // Clear destinations
    memset(dest1, 'X', 10);
    memset(dest2, 'X', 10);
    
    // Test normal strlcpy
    result1 = strlcpy(dest1, src, 10);
    result2 = ft_strlcpy(dest2, src, 10);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcpy_truncation(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "This is a long string";
    char dest1[10];
    char dest2[10];
    size_t result1, result2;
    
    // Clear destinations
    memset(dest1, 'X', 10);
    memset(dest2, 'X', 10);
    
    // Test truncation
    result1 = strlcpy(dest1, src, 10);
    result2 = ft_strlcpy(dest2, src, 10);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcpy_zero_size(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "Test";
    char dest1[10] = "Original";
    char dest2[10] = "Original";
    size_t result1, result2;
    
    // Test with zero size - should not modify destination
    result1 = strlcpy(dest1, src, 0);
    result2 = ft_strlcpy(dest2, src, 0);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcpy_empty_string(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "";
    char dest1[10];
    char dest2[10];
    size_t result1, result2;
    
    // Clear destinations
    memset(dest1, 'X', 10);
    memset(dest2, 'X', 10);
    
    // Test empty string
    result1 = strlcpy(dest1, src, 10);
    result2 = ft_strlcpy(dest2, src, 10);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcpy_exact_fit(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "Exact";
    char dest1[6];
    char dest2[6];
    size_t result1, result2;
    
    // Clear destinations
    memset(dest1, 'X', 6);
    memset(dest2, 'X', 6);
    
    // Test exact fit (5 chars + null terminator = 6)
    result1 = strlcpy(dest1, src, 6);
    result2 = ft_strlcpy(dest2, src, 6);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcpy_empty_string_overflow(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "";
    char dest1[1];
    char dest2[1];
    size_t result1, result2;
    
    // Clear destinations with a non-null character
    dest1[0] = 'X';
    dest2[0] = 'X';
    
    // Test empty string with size 1 buffer (would overflow if source had content)
    result1 = strlcpy(dest1, src, 1);
    result2 = ft_strlcpy(dest2, src, 1);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    munit_assert_char(dest1[0], ==, '\0'); // Should be null terminated
    munit_assert_char(dest2[0], ==, '\0'); // Should be null terminated
    return MUNIT_OK;
}

static MunitResult test_ft_strlcpy_dest_overflow(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "This is a very long string that will definitely overflow a small buffer";
    char dest1[5];
    char dest2[5];
    size_t result1, result2;
    
    // Clear destinations
    memset(dest1, 'X', 5);
    memset(dest2, 'X', 5);
    
    // Test destination overflow - should truncate and null-terminate
    result1 = strlcpy(dest1, src, 5);
    result2 = ft_strlcpy(dest2, src, 5);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    munit_assert_size(strlen(dest1), ==, 4); // Should have 4 chars + null terminator
    munit_assert_size(strlen(dest2), ==, 4); // Should have 4 chars + null terminator
    munit_assert_char(dest1[4], ==, '\0'); // Should be null terminated
    munit_assert_char(dest2[4], ==, '\0'); // Should be null terminated
    munit_assert_size(result1, ==, strlen(src)); // Should return length of source
    munit_assert_size(result2, ==, strlen(src)); // Should return length of source
    return MUNIT_OK;
}

static MunitResult test_ft_strlcpy_large_buffer_empty_string(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "";
    char dest1[1024];
    char dest2[1024];
    size_t result1, result2;
    
    memset(dest1, 'X', 1024);
    memset(dest2, 'X', 1024);
    
    result1 = strlcpy(dest1, src, 5);
    result2 = ft_strlcpy(dest2, src, 5);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    munit_assert_size(strlen(dest1), ==, 0);
    munit_assert_size(strlen(dest2), ==, 0);
    munit_assert_size(result1, ==, strlen(src));
    munit_assert_size(result2, ==, strlen(src));
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_strlcpy[] = {
    { "/normal", test_ft_strlcpy_normal, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/truncation", test_ft_strlcpy_truncation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero_size", test_ft_strlcpy_zero_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/empty_string", test_ft_strlcpy_empty_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/empty_string_overflow", test_ft_strlcpy_empty_string_overflow, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/dest_overflow", test_ft_strlcpy_dest_overflow, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/exact_fit", test_ft_strlcpy_exact_fit, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/large_buffer_empty_string", test_ft_strlcpy_large_buffer_empty_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Test suite */
const MunitSuite test_suite_ft_strlcpy = {
    "/test_ft_strlcpy",
    tests_ft_strlcpy,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
