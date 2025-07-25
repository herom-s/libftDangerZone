#include "munit.h"
#include "libft.h"
#include <bsd/string.h>
#include <stdlib.h>

static MunitResult test_ft_strlcat_normal(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char dest1[20] = "Hello";
    char dest2[20] = "Hello";
    char src[] = " World";
    size_t result1, result2;
    
    // Test normal strlcat
    result1 = strlcat(dest1, src, 20);
    result2 = ft_strlcat(dest2, src, 20);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcat_truncation(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char dest1[10] = "Hello";
    char dest2[10] = "Hello";
    char src[] = " World!";
    size_t result1, result2;
    
    // Test truncation
    result1 = strlcat(dest1, src, 10);
    result2 = ft_strlcat(dest2, src, 10);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcat_empty_dest(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char dest1[20] = "";
    char dest2[20] = "";
    char src[] = "Hello";
    size_t result1, result2;
    
    // Test with empty destination
    result1 = strlcat(dest1, src, 20);
    result2 = ft_strlcat(dest2, src, 20);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcat_empty_src(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char dest1[20] = "Hello";
    char dest2[20] = "Hello";
    char src[] = "";
    size_t result1, result2;
    
    // Test with empty source
    result1 = strlcat(dest1, src, 20);
    result2 = ft_strlcat(dest2, src, 20);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcat_size_too_small(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char dest1[20] = "Hello";
    char dest2[20] = "Hello";
    char src[] = " World";
    size_t result1, result2;
    
    // Test with size smaller than dest length
    result1 = strlcat(dest1, src, 3);
    result2 = ft_strlcat(dest2, src, 3);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_strlcat_exact_fit(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char dest1[12] = "Hello";
    char dest2[12] = "Hello";
    char src[] = " World";
    size_t result1, result2;
    
    // Test exact fit (5 + 6 + 1 = 12)
    result1 = strlcat(dest1, src, 12);
    result2 = ft_strlcat(dest2, src, 12);
    
    munit_assert_size(result1, ==, result2);
    munit_assert_string_equal(dest1, dest2);
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_strlcat[] = {
    { "/normal", test_ft_strlcat_normal, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/truncation", test_ft_strlcat_truncation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/empty_dest", test_ft_strlcat_empty_dest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/empty_src", test_ft_strlcat_empty_src, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/size_too_small", test_ft_strlcat_size_too_small, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/exact_fit", test_ft_strlcat_exact_fit, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Test suite */
const MunitSuite test_suite_ft_strlcat = {
    "/test_ft_strlcat",
    tests_ft_strlcat,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
