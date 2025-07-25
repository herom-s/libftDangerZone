#include "munit.h"
#include "libft.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static MunitResult test_ft_memmove_no_overlap(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char src[] = "Hello, World!";
    char dest1[20];
    char dest2[20];
    
    // Clear destinations
    memset(dest1, 0, 20);
    memset(dest2, 0, 20);
    
    // Test non-overlapping memmove
    memmove(dest1, src, strlen(src));
    ft_memmove(dest2, src, strlen(src));
    
    munit_assert_memory_equal(strlen(src), dest1, dest2);
    return MUNIT_OK;
}

static MunitResult test_ft_memmove_overlap_forward(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char buffer1[] = "123456789";
    char buffer2[] = "123456789";
    
    // Move overlapping regions (forward overlap)
    memmove(buffer1 + 2, buffer1, 5);
    ft_memmove(buffer2 + 2, buffer2, 5);
    
    munit_assert_memory_equal(9, buffer1, buffer2);
    return MUNIT_OK;
}

static MunitResult test_ft_memmove_overlap_backward(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char buffer1[] = "123456789";
    char buffer2[] = "123456789";
    
    // Move overlapping regions (backward overlap)
    memmove(buffer1, buffer1 + 2, 5);
    ft_memmove(buffer2, buffer2 + 2, 5);
    
    munit_assert_memory_equal(9, buffer1, buffer2);
    return MUNIT_OK;
}

static MunitResult test_ft_memmove_zero_size(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char buffer1[] = "Original";
    char buffer2[] = "Original";
    
    // Test with zero size - should not change anything
    memmove(buffer1, buffer1 + 2, 0);
    ft_memmove(buffer2, buffer2 + 2, 0);
    
    munit_assert_memory_equal(8, buffer1, buffer2);
    return MUNIT_OK;
}

static MunitResult test_ft_memmove_same_pointer(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
    
    char buffer1[] = "SamePointer";
    char buffer2[] = "SamePointer";
    
    // Test moving to same location
    memmove(buffer1, buffer1, 5);
    ft_memmove(buffer2, buffer2, 5);
    
    munit_assert_memory_equal(11, buffer1, buffer2);
    return MUNIT_OK;
}

static MunitResult test_ft_memmove_null_src_segfault(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	pid_t pid;
    int status;
    int memmove_segfaulted = 0;
    int ft_memmove_segfaulted = 0;

    pid = fork();
    if (pid == 0) {
		char	*src = (void *) 0;
		char	dest[10];
		memmove(dest, src, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            memmove_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    pid = fork();
    if (pid == 0) {
		char	*src = (void *) 0;
		char	dest[10];
		ft_memmove(dest, src, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            ft_memmove_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    munit_assert_int(memmove_segfaulted, ==, 1);
    munit_assert_int(ft_memmove_segfaulted, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_ft_memmove_null_dest_segfault(const MunitParameter params[], void* data) {
    (void) params;
    (void) data;
	pid_t pid;
    int status;
    int memmove_segfaulted = 0;
    int ft_memmove_segfaulted = 0;

    pid = fork();
    if (pid == 0) {
		char	src[10] = "test";
		char	*dest = (void *) 0;
		memmove(dest, src, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            memmove_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    pid = fork();
    if (pid == 0) {
		char	src[10] = "test";
		char	*dest = (void *) 0;
		ft_memmove(dest, src, 10);
        exit(0);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV) {
            ft_memmove_segfaulted = 1;
        }
    } else {
        munit_error("fork() failed");
    }
    
    munit_assert_int(memmove_segfaulted, ==, 1);
    munit_assert_int(ft_memmove_segfaulted, ==, 1);
    return MUNIT_OK;
}

/* Test array */
static MunitTest tests_ft_memmove[] = {
    { "/no_overlap", test_ft_memmove_no_overlap, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/overlap_forward", test_ft_memmove_overlap_forward, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/overlap_backward", test_ft_memmove_overlap_backward, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/zero_size", test_ft_memmove_zero_size, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/same_pointer", test_ft_memmove_same_pointer, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/null_src_segfault", test_ft_memmove_null_src_segfault, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/null_dest_segfault", test_ft_memmove_null_dest_segfault, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Test suite */
const MunitSuite test_suite_ft_memmove = {
    "/test_ft_memmove",
    tests_ft_memmove,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};
