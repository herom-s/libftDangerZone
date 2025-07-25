#include "munit.h"
#include "libft.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static MunitResult test_ft_memcpy_normal(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "Hello, World!";
    char dest1[20];
    char dest2[20];
    
    // Clear destinations
    memset(dest1, 0, 20);
    memset(dest2, 0, 20);
    
    // Test memcpy
    memcpy(dest1, src, strlen(src));
    ft_memcpy(dest2, src, strlen(src));
    
    munit_assert_memory_equal(strlen(src), dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_memcpy_zero_size(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "Test";
    char dest1[10] = "Original";
    char dest2[10] = "Original";
    
    // Test with zero size - should not change destination
    memcpy(dest1, src, 0);
    ft_memcpy(dest2, src, 0);
    
    munit_assert_memory_equal(10, dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_memcpy_binary_data(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    unsigned char src[] = {0x00, 0xFF, 0xAA, 0x55, 0x0F, 0xF0};
    unsigned char dest1[10];
    unsigned char dest2[10];
    
    // Clear destinations
    memset(dest1, 0, 10);
    memset(dest2, 0, 10);
    
    // Test with binary data
    memcpy(dest1, src, 6);
    ft_memcpy(dest2, src, 6);
    
    munit_assert_memory_equal(6, dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_memcpy_large_size(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    size_t size = 1000;
    char *src = malloc(size);
    char *dest1 = malloc(size);
    char *dest2 = malloc(size);
    
    // Fill source with pattern
    for (size_t i = 0; i < size; i++) {
        src[i] = i % 256;
    }
    
    // Test large copy
    memcpy(dest1, src, size);
    ft_memcpy(dest2, src, size);
    
    munit_assert_memory_equal(size, dest1, dest2);
    
    free(src);
    free(dest1);
    free(dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_memcpy_null_src_segfault(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	pid_t pid;
    int status;
    int memcpy_segfaulted = 0;
    int ft_memcpy_segfaulted = 0;

    pid = fork();
    if (pid == 0) {
		char	*src = (void *) 0;
		char	dest[10];
		memcpy(dest, src, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            memcpy_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    pid = fork();
    if (pid == 0) {
		char	*src = (void *) 0;
		char	dest[10];
		ft_memcpy(dest, src, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            ft_memcpy_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    munit_assert_int(memcpy_segfaulted, ==, 1);
    munit_assert_int(ft_memcpy_segfaulted, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_ft_memcpy_null_dest_segfault(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	pid_t pid;
    int status;
    int memcpy_segfaulted = 0;
    int ft_memcpy_segfaulted = 0;

    pid = fork();
    if (pid == 0) {
		char	src[10] = "test";
		char	*dest = (void *) 0;
		memcpy(dest, src, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            memcpy_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    pid = fork();
    if (pid == 0) {
		char	src[10] = "test";
		char	*dest = (void *) 0;
		ft_memcpy(dest, src, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            ft_memcpy_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    munit_assert_int(memcpy_segfaulted, ==, 1);
    munit_assert_int(ft_memcpy_segfaulted, ==, 1);
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_memcpy[] = {
    { "/normal", test_ft_memcpy_normal, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero_size", test_ft_memcpy_zero_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/binary_data", test_ft_memcpy_binary_data, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/large_size", test_ft_memcpy_large_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/null_src_segfault", test_ft_memcpy_null_src_segfault, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/null_dest_segfault", test_ft_memcpy_null_dest_segfault, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Test suite */
const MunitSuite test_suite_ft_memcpy = {
    "/test_ft_memcpy",
    tests_ft_memcpy,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
